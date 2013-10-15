# =XMPP4R - XMPP Library for Ruby
# License:: Ruby's license (see the LICENSE file) or GNU GPL, at your option.
# Website::http://home.gna.org/xmpp4r/

require 'xmpp4r'
require 'xmpp4r/discovery'
require 'xmpp4r/dataforms'
require 'xmpp4r/caps/c'
require 'digest'
require 'xmpp4r/base64'

module Jabber
  module Caps
    def self.generate_ver_str(identities, features, forms=[])
      # 1.  Initialize an empty string S.
      s = ''

      # 2. Sort the service discovery identities [14] by category and
      # then by type (if it exists) and then by xml:lang (if it
      # exists), formatted as CATEGORY '/' [TYPE] '/' [LANG] '/'
      # [NAME]. Note that each slash is included even if the TYPE,
      # LANG, or NAME is not included.
      identities.sort! do |identity1,identity2|
        cmp_result = nil
        [:category, :type, :xml_lang, :iname].each do |field|
          value1 = identity1.send(field)
          value2 = identity2.send(field)

          if value1 != value2
            cmp_result = value1 <=> value2
            break
          end
        end


        cmp_result
      end

      # 3. For each identity, append the 'category/type/lang/name' to
      # S, followed by the '<' character.
      s += identities.collect do |identity|
        [:category, :type, :xml_lang, :iname].collect do |field|
          identity.send(field).to_s
        end.join('/') + '<'
      end.join

      # 4. Sort the supported service discovery features. [15]
      features.sort! do |feature1,feature2|
        feature1.var <=> feature2.var
      end

      # 5. For each feature, append the feature to S, followed by the
      # '<' character.
      s += features.collect do |feature|
        feature.var.to_s + '<'
      end.join

      # 6. If the service discovery information response includes
      # XEP-0128 data forms, sort the forms by the FORM_TYPE (i.e., by
      # the XML character data of the <value/> element).
      forms.sort! do |form1,form2|
        fform_type1 = form1.field('FORM_TYPE')
        fform_type2 = form2.field('FORM_TYPE')
        form_type1 = fform_type1 ? fform_type1.values.to_s : nil
        form_type2 = fform_type2 ? fform_type2.values.to_s : nil
        form_type1 <=> form_type2
      end

      # 7. For each extended service discovery information form:
      forms.each do |form|
        # 7.1. Append the XML character data of the FORM_TYPE field's
        # <value/> element, followed by the '<' character.
        fform_type = form.field('FORM_TYPE')
        form_type = fform_type ? fform_type.values.to_s : nil
        s += "#{form_type}<"

        # 7.2. Sort the fields by the value of the "var" attribute.
        fields = form.fields(false).sort do |field1,field2|
          field1.var <=> field2.var
        end

        # 7.3. For each field:

        fields.each do |field|
          # 7.3.1. Append the value of the "var" attribute, followed by
          # the '<' character.
          s += "#{field.var}<"

          # 7.3.2. Sort values by the XML character data of the <value/>
          # element.
          values = field.values.sort do |value1,value2|
            value1 <=> value2
          end

          # 7.3.3. For each <value/> element, append the XML character
          # data, followed by the '<' character.
          s += values.collect do |value|
            "#{value}<"
          end.join
        end
      end

      # 8. Ensure that S is encoded according to the UTF-8 encoding
      # (RFC 3269 [16]).

      # (given in XMPP4R)

      s
    end

    ##
    # Implementation of the algorithm defined at:
    # http://www.xmpp.org/extensions/xep-0115.html#ver-gen
    def self.generate_ver(identities, features, forms=[], hash='sha-1')
      s = generate_ver_str(identities, features, forms)

      # 9. Compute the verification string by hashing S using the
      # algorithm specified in the 'hash' attribute (e.g., SHA-1 as
      # defined in RFC 3174 [17]). The hashed data MUST be generated
      # with binary output and encoded using Base64 as specified in
      # Section 4 of RFC 4648 [18] (note: the Base64 output MUST NOT
      # include whitespace and MUST set padding bits to zero). [19]

      # See http://www.iana.org/assignments/hash-function-text-names
      hash_klass = case hash
                     when 'md2' then nil
                     when 'md5' then Digest::MD5
                     when 'sha-1' then Digest::SHA1
                     when 'sha-224' then nil
                     when 'sha-256' then Digest::SHA256
                     when 'sha-384' then Digest::SHA384
                     when 'sha-512' then Digest::SHA512
                   end
      if hash_klass
        Base64::encode64(hash_klass::digest(s)).strip
      else
        nil
      end
    end

    ##
    # Generate a ver hash from a Jabber::Discovery::IqQueryDiscoInfo result
    # query:: [Jabber::Discovery::IqQueryDiscoInfo]
    def self.generate_ver_from_discoinfo(query, hash='sha-1')
      identities = []
      features = []
      forms = []
      query.each_element do |element|
        if element.kind_of? Discovery::Identity
          identities << element
        elsif element.kind_of? Discovery::Feature
          features << element
        elsif element.kind_of? Dataforms::XData
          forms << element
        end
      end
      generate_ver(identities, features, forms, hash)
    end
  end
end
