# Not sure if this is an IRB bug, but thought you guys should know.
#
# ** My Ruby version: ruby 1.8.7 (2009-06-12 patchlevel 174) [x86_64-linux]
# ** Version of Rubygems: 1.3.5
# ** Version of the Curb gem: 0.6.6.0
#
#
# Transcript of IRB session:
# ------------------------------------------------------------------------------------------------------------------
# irb(main):001:0>  a =  {
# irb(main):002:1*     :type => :pie,
# irb(main):003:1*     :series => {
# irb(main):004:2*       :names => [:a,:b],
# irb(main):005:2*       :values => [70,30],
# irb(main):006:2*       :colors => [:red,:green]
# irb(main):007:2>     },
# irb(main):008:1*     :output_format => :png
# irb(main):009:1>   }
# => {:type=>:pie, :output_format=>:png, :series=>{:names=>[:a, :b], :values=>[70, 30], :colors=>[:red, :green]}}
# irb(main):010:0> post = []
# => []
# irb(main):011:0> require 'rubygems'
# => true
# irb(main):012:0> require 'curb'
# => true
# irb(main):013:0> include Curl
# => Object
# irb(main):014:0> a.each_pair do |k,v|
# irb(main):015:1* post << PostField.content(k,v)
# irb(main):016:1> end
# => {:type=>:pie, :output_format=>:png, :series=>{:names=>[:a, :b], :values=>[70, 30], :colors=>[:red, :green]}}
# irb(main):017:0> post
# /usr/lib/ruby/1.8/irb.rb:302: [BUG] Segmentation fault
# ruby 1.8.7 (2009-06-12 patchlevel 174) [x86_64-linux]
#
# Aborted
# ------------------------------------------------------------------------------------------------------------------
require File.expand_path(File.join(File.dirname(__FILE__), 'helper'))

class BugPostFieldsCrash2 < Test::Unit::TestCase
  def test_crash
    a =  {
       :type => :pie,
       :series => {
         :names => [:a,:b],
         :values => [70,30],
         :colors => [:red,:green]
       },
       :output_format => :png
    }
    post = []
    a.each_pair do |k,v|
      post << Curl::PostField.content(k,v)
    end
    post.inspect
  end
end
