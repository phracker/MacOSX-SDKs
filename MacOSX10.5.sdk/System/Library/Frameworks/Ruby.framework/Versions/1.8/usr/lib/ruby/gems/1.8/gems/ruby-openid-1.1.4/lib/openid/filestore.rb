require 'fileutils'
require 'pathname'
require 'tempfile'

require 'openid/util'
require 'openid/stores'
require 'openid/association'

module OpenID

  # Filesystem-based store for OpenID associations and nonces.
  #
  # Methods of this object may raise SystemCallError if filestystem
  # related errors are encountered.
  class FilesystemStore < Store
  
    @@FILENAME_ALLOWED = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ.-".split("")
  
    # Create a FilesystemStore instance, putting all data in +directory+.
    def initialize(directory)
      p_dir = Pathname.new(directory)
      @nonce_dir = p_dir.join('nonces')
      @association_dir = p_dir.join('associations')
      @temp_dir = p_dir.join('temp')
      @auth_key_name = p_dir.join('auth_key')
      @max_nonce_age = 6 * 60 * 60
      
      self.ensure_dir(@nonce_dir)
      self.ensure_dir(@association_dir)
      self.ensure_dir(@temp_dir)
      self.ensure_dir(File.dirname(@auth_key_name))
    end

    # Read the auth key from the auth key file. Returns nil if there
    # is currently no auth key.
    def read_auth_key
      f = nil
      begin
        f = File.open(@auth_key_name)      
      rescue Errno::ENOENT
        return nil
      else
        return f.read
      ensure
        f.close unless f.nil?      
      end
    end

    # Generate a new random auth key and safely store it in the location
    # specified by @auth_key_name
    def create_auth_key
      auth_key = OpenID::Util.random_string(@@AUTH_KEY_LEN)
      f, tmp = mktemp
      begin
        begin
          f.write(auth_key)
          f.fsync
        ensure
          f.close
        end
        begin
          begin
            File.link(tmp, @auth_key_name)
          rescue NotImplementedError # no link under windows
            File.rename(tmp, @auth_key_name)
          end
        rescue Errno::EEXIST
          raise if read_auth_key.nil?
        end      
      ensure
        self.remove_if_present(tmp)
      end

      auth_key
    end
    
    # Retrieve the auth key from the file specified by
    # @auth_key_file, creating it if it does not exist
    def get_auth_key
      auth_key = read_auth_key
      if auth_key.nil?
        auth_key = create_auth_key
      end
      
      if auth_key.length != @@AUTH_KEY_LEN
        raise StandardError.new("Bad auth key - wrong length")
      end
      
      auth_key
    end

    # Create a unique filename for a given server url and handle. The
    # filename that is returned will contain the domain name from the
    # server URL for ease of human inspection of the data dir.
    def get_association_filename(server_url, handle)      
      filename = self.filename_from_url(server_url)
      filename += '-' + safe64(handle)
      @association_dir.join(filename)
    end

    # Store an association in the assoc directory
    def store_association(server_url, association)
      assoc_s = OpenID::Association.serialize(association)
      filename = get_association_filename(server_url, association.handle)
      f, tmp = mktemp
    
      begin
        begin
          f.write(assoc_s)
          f.fsync
        ensure
          f.close
        end
        
        begin
          File.rename(tmp, filename)
        rescue Errno::EEXIST
        
          begin
            File.unlink(filename)
          rescue Errno::ENOENT
            # do nothing
          end
          
          File.rename(tmp, filename)
        end
        
      rescue
        self.remove_if_present(tmp)
        raise
      end
    end
    
    # Retrieve an association
    def get_association(server_url, handle=nil)
      unless handle.nil?
        filename = get_association_filename(server_url, handle)
        return _get_association(filename)
      end
      
      # search though existing files looking for a match
      prefix = filename_from_url(server_url)
      assoc_filenames = Dir.entries(@association_dir)
      assoc_filenames = assoc_filenames.find_all { |f| f.index(prefix) == 0 }
      
      assocs = assoc_filenames.collect do |f|
        _get_association(@association_dir.join(f))
      end

      assocs = assocs.find_all { |a| not a.nil? }
      assocs = assocs.sort_by { |a| a.issued }
      
      return nil if assocs.empty?
      return assocs[-1]
    end

    def _get_association(filename)
      begin
        assoc_file = File.open(filename, "r")
      rescue Errno::ENOENT
        return nil
      else
        begin
          assoc_s = assoc_file.read
        ensure
          assoc_file.close
        end
        
        begin
          association = OpenID::Association.deserialize(assoc_s)      
        rescue
          self.remove_if_present(filename)
          return nil
        end

        # clean up expired associations
        if association.expires_in == 0
          self.remove_if_present(filename)
          return nil
        else
          return association
        end
      end
    end

    # Remove an association if it exists, otherwise do nothing.
    def remove_association(server_url, handle)
      assoc = get_association(server_url, handle)
      
      if assoc.nil?
        return false
      else
        filename = get_association_filename(server_url, handle)
        return self.remove_if_present(filename)
      end
    end

    # Mark this nonce as present    
    def store_nonce(nonce)
      filename = @nonce_dir.join(nonce)
      File.open(filename, "w").close
    end

    # Return whether this nonce is present.  As a side-effect, mark it 
    # as no longer present.
    def use_nonce(nonce)
      filename = @nonce_dir.join(nonce)
      begin
        st = File.stat(filename)
      rescue Errno::ENOENT
        return false
      else
        begin
          File.unlink(filename)
        rescue Errno::ENOENT
          return false
        end      
        nonce_age = Time.now.to_f - st.mtime.to_f
        nonce_age <= @max_nonce_age
      end
    end

    # Garbage collection routine.  Clean up old associations and nonces.
    def clean
      nonces = Dir[@nonce_dir.join("*")]
      now = Time.now
      
      nonces.each do |nonce|
        filename = nonce_dir.join(nonce)
        begin
          st = File.stat(filename)
        rescue Errno::ENOENT
          next
        else
          nonce_age = now - st.mtime
          self.remove_if_present(filename) if nonce_age > @max_nonce_age
        end
      end

      association_filenames = Dir[@association_dir.join("*")]
      association_filenames.each do |af|
        begin
          f = File.open(af, 'r')
        rescue Errno::ENOENT
          next
        else
          begin
            assoc_s = f.read
          ensure
            f.close
          end
          begin
            association = OpenID::Association.deserialize(assoc_s)
          rescue "VersionError"
            self.remove_if_present(af)
            next
          else
            self.remove_if_present(af) if association.expires_in == 0          
          end
        end
      end
    end

    protected

    # Create a temporary file and return the File object and filename.    
    def mktemp
      f = Tempfile.new('tmp', @temp_dir)
      [f, f.path]
    end

    # create a safe filename from a url
    def filename_from_url(url)
      filename = []
      url.sub('://','-').split("").each do |c|
        if @@FILENAME_ALLOWED.index(c)
          filename << c
        else
          filename << sprintf("_%02X", c[0])
        end    
      end
      filename.join("")
    end

    def safe64(s)
      s = OpenID::Util.sha1(s)
      s = OpenID::Util.to_base64(s)
      s.gsub!('+', '_')
      s.gsub!('/', '.')
      s.gsub!('=', '')
      return s
    end

    # remove file if present in filesystem
    def remove_if_present(filename)
      begin
        File.unlink(filename)
      rescue Errno::ENOENT
        return false
      end
      return true
    end
  
    # ensure that a path exists

    def ensure_dir(dir_name)
      FileUtils::mkdir_p(dir_name)
    end
    
  end

end



