#!/usr/bin/env ruby

require 'mkmf'

def crash(str)
  printf(" extconf failure: %s\n", str)
  exit 1
end

xc = with_config('xml2-config')
if xc
  cflags = `#{xc} --cflags`.chomp
  if $? != 0
    cflags = nil
  else
    libs = `#{xc} --libs`.chomp
    if $? != 0
      libs = nil
    else
      $CFLAGS += ' ' + cflags
      $libs = libs + " " + $libs
    end
  end
else
  dir_config('xml2')
end

found_header = find_header('libxml/xmlversion.h',
                           '/opt/include/libxml2',
                           '/opt/local/include/libxml2',
                           '/usr/local/include/libxml2',
                           '/usr/include/libxml2',
                           '/usr/local/include')

found_lib = find_library('xml2', 'xmlParseDoc',
                         '/opt/lib',
                         '/opt/local/lib',
                         '/usr/local/lib',
                         '/usr/lib')

found_lib ||= find_library('libxml2', 'xmlParseDoc',
                           '/opt/lib',
                           '/opt/local/lib',
                           '/usr/local/lib',
                           '/usr/lib')

if !found_header || !found_lib
    crash(<<~EOL)
      Cannot find libxml2.

      Install the library or try one of the following options to extconf.rb:
  
        --with-xml2-config=/path/to/xml2-config
        --with-xml2-dir=/path/to/libxml2
        --with-xml2-lib=/path/to/libxml2/lib
        --with-xml2-include=/path/to/libxml2/include
    EOL
end

create_header()
create_makefile('libxml_ruby')
