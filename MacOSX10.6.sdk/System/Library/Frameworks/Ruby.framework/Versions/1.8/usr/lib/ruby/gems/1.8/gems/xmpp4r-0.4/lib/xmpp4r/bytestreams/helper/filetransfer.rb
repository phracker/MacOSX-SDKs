# =XMPP4R - XMPP Library for Ruby
# License:: Ruby's license (see the LICENSE file) or GNU GPL, at your option.
# Website::http://home.gna.org/xmpp4r/

require 'xmpp4r/callbacks'
require 'xmpp4r/bytestreams/iq/si'
require 'xmpp4r/dataforms/x/data'
require 'xmpp4r/bytestreams/helper/ibb/base'
require 'xmpp4r/bytestreams/helper/socks5bytestreams/base'

module Jabber
  module FileTransfer
    ##
    # The TransferSource is an interface (Mix-in)
    # which sources for FileTransfer#offer should include
    module TransferSource
      ##
      # Filename of the offered file
      def filename
      end
      ##
      # Mime-type of the offered file, can be nil
      def mime
      end
      ##
      # Size of the offered file
      def size
      end
      ##
      # MD5-Sum of the offered file, can be nil
      def md5
      end
      ##
      # Date of the offered file, can be nil
      def date
      end
      ##
      # Read a chunk from the source
      #
      # If this is a ranged transfer, it should
      # implement length checking
      # length:: [Fixnum]
      def read(length=nil)
      end
      ##
      # Seek in the source for ranged transfers
      def seek(position)
      end
      ##
      # Set the amount of data to send for ranged transfers
      def length=(l)
      end
      ##
      # Does implement the methods seek and length= ?
      #
      # FileTransfer will only then offer a ranged transfer.
      # result:: [false] or [true]
      def can_range?
        false
      end
    end

    ##
    # Simple implementation of TransferSource
    # for sending simple files
    # (supports ranged transfers)
    class FileSource
      include TransferSource

      def initialize(filename)
        @file = File.new(filename)
        @filename = filename
        @bytes_read = 0
        @length = nil
      end

      def filename
        File::basename @filename
      end

      ##
      # Everything is 'application/octet-stream'
      def mime
        'application/octet-stream'
      end

      def size
        File.size @filename
      end

      def date
        @file.mtime
      end

      ##
      # Because it can_range?, this method implements length checking
      def read(length=512)
        if @length
          return nil if @bytes_read >= @length  # Already read everything requested
          if @bytes_read + length > @length # Will we read more than requested?
            length = @length - @bytes_read  # Truncate it!
          end
        end

        buf = @file.read(length)
        @bytes_read += buf.size if buf
        buf
      end

      def seek(position)
        @file.seek(position)
      end

      def length=(l)
        @length = l
      end

      def can_range?
        true
      end
    end

    ##
    # The FileTransfer helper provides the ability to respond
    # to incoming and to offer outgoing file-transfers.
    class Helper
      ##
      # Set this if you want to use this helper in a Component
      attr_accessor :my_jid
      ##
      # Set this to false if you don't want to use SOCKS5Bytestreams
      attr_accessor :allow_bytestreams
      ##
      # Set this to false if you don't want to use IBB
      attr_accessor :allow_ibb

      ##
      # Create a new FileTransfer instance
      def initialize(stream)
        @stream = stream
        @my_jid = nil
        @allow_bytestreams = true
        @allow_ibb = true

        @incoming_cbs = CallbackList.new

        @stream.add_iq_callback(150, self) { |iq|
          if iq.type == :set
            file = iq.first_element('si/file')
            field = nil
            iq.each_element('si/feature/x') { |e| field = e.field('stream-method') }

            if file and field
              @incoming_cbs.process(iq, file)
              true
            else
              false
            end
          else
            false
          end
        }
      end

      ##
      # Add a callback which will be invoked upon an incoming file-transfer
      #
      # block takes two arguments:
      # * Iq
      # * Bytestreams::IqSiFile in the Iq
      # You may then invoke accept or decline
      def add_incoming_callback(priority = 0, ref = nil, &block)
        @incoming_cbs.add(priority, ref, block)
      end

      ##
      # Accept an incoming file-transfer,
      # to be used in a block given to add_incoming_callback
      #
      # offset and length will be ignored if there is no
      # 'si/file/range' in iq.
      # iq:: [Iq] of file-transfer we want to accept
      # offset:: [Fixnum] or [nil]
      # length:: [Fixnum] or [nil]
      # result:: [Bytestreams::SOCKS5BytestreamsTarget] or [Bytestreams::IBBTarget] or [nil] if no valid stream-method
      def accept(iq, offset=nil, length=nil)
        oldsi = iq.first_element('si')

        answer = iq.answer(false)
        answer.type = :result

        si = answer.add(Bytestreams::IqSi.new)
        if (offset or length) and oldsi.file.range
          si.add(Bytestreams::IqSiFile.new)
          si.file.add(Bytestreams::IqSiFileRange.new(offset, length))
        end
        si.add(FeatureNegotiation::IqFeature.new.import(oldsi.feature))
        si.feature.x.type = :submit
        stream_method = si.feature.x.field('stream-method')

        if stream_method.options.keys.include?(Bytestreams::NS_BYTESTREAMS) and @allow_bytestreams
          stream_method.values = [Bytestreams::NS_BYTESTREAMS]
          stream_method.options = []
          @stream.send(answer)

          Bytestreams::SOCKS5BytestreamsTarget.new(@stream, oldsi.id, iq.from, iq.to)
        elsif stream_method.options.keys.include?(Bytestreams::IBB::NS_IBB) and @allow_ibb
          stream_method.values = [Bytestreams::IBB::NS_IBB]
          stream_method.options = []
          @stream.send(answer)

          Bytestreams::IBBTarget.new(@stream, oldsi.id, iq.from, iq.to)
        else
          eanswer = iq.answer(false)
          eanswer.type = :error
          eanswer.add(ErrorResponse.new('bad-request')).type = :cancel
          eanswer.error.add(REXML::Element.new('no-valid-streams')).add_namespace('http://jabber.org/protocol/si')
          @stream.send(eanswer)

          nil
        end
      end

      ##
      # Decline an incoming file-transfer,
      # to be used in a block given to add_incoming_callback
      # iq:: [Iq] of file-transfer we want to decline
      def decline(iq)
        answer = iq.answer(false)
        answer.type = :error
        error = answer.add(ErrorResponse.new('forbidden', 'Offer declined'))
        error.type = :cancel
        @stream.send(answer)
      end

      ##
      # Offer a file to somebody
      #
      # Will wait for a response from the peer
      #
      # The result is a stream which you can configure, or nil
      # if the peer responded with an invalid stream-method.
      #
      # May raise an ServerError
      # jid:: [JID] to send the file to
      # source:: File-transfer source, implementing the FileSource interface
      # desc:: [String] or [nil] Optional file description
      # from:: [String] or [nil] Optional jid for components
      # result:: [Bytestreams::SOCKS5BytestreamsInitiator] or [Bytestreams::IBBInitiator] or [nil]
      def offer(jid, source, desc=nil, from=nil)
        from = from || @my_jid || @stream.jid
        session_id = Jabber::IdGenerator.instance.generate_id

        offered_methods = {}
        if @allow_bytestreams
          offered_methods[Bytestreams::NS_BYTESTREAMS] = nil
        end
        if @allow_ibb
          offered_methods[Bytestreams::IBB::NS_IBB] = nil
        end

        iq = Iq.new(:set, jid)
        iq.from = from
        si = iq.add(Bytestreams::IqSi.new(session_id, Bytestreams::PROFILE_FILETRANSFER, source.mime))

        file = si.add(Bytestreams::IqSiFile.new(source.filename, source.size))
        file.hash = source.md5
        file.date = source.date
        file.description = desc if desc
        file.add(Bytestreams::IqSiFileRange.new) if source.can_range?

        feature = si.add(REXML::Element.new('feature'))
        feature.add_namespace 'http://jabber.org/protocol/feature-neg'
        x = feature.add(Dataforms::XData.new(:form))
        stream_method_field = x.add(Dataforms::XDataField.new('stream-method', :list_single))
        stream_method_field.options = offered_methods

        begin
          stream_method = nil
          response = nil
          @stream.send_with_id(iq) do |r|
            response = r
            si = response.first_element('si')
            if si and si.feature and si.feature.x
              stream_method = si.feature.x.field('stream-method').values.first

              if si.file and si.file.range
                if source.can_range?
                  source.seek(si.file.range.offset) if si.file.range.offset
                  source.length = si.file.range.length if si.file.range.length
                else
                  source.read(si.file.range.offset)
                end
              end
            end
          end
        rescue ServerError => e
          if e.error.code == 403  # Declined
            return false
          else
            raise e
          end
        end

        if stream_method == Bytestreams::NS_BYTESTREAMS and @allow_bytestreams
          Bytestreams::SOCKS5BytestreamsInitiator.new(@stream, session_id, from, jid)
        elsif stream_method == Bytestreams::IBB::NS_IBB and @allow_ibb
          Bytestreams::IBBInitiator.new(@stream, session_id, from, jid)
        else  # Target responded with a stream_method we didn't offer
          eanswer = response.answer
          eanswer.type = :error
          eanswer.add ErrorResponse.new('bad-request')
          @stream.send(eanswer)
          nil
        end
      end
    end
  end
end
