# $Id: libxml.rb,v 1.5.2.1 2006/11/26 12:37:42 roscopeco Exp $ 
# Please see the LICENSE file for copyright and distribution information 
require 'xml/libxml_so'

class XML::Document
  include Enumerable

  # maybe, maybe not...
  def each(&blk)
    find('//*').each(&blk)
  end
end

class XML::Node::Set 
  include Enumerable
  
  # inefficient, but maybe can find a way to cache the
  # ary and dump on change?
  def [](i, count = nil) 
    if count
      to_a[i,count]
    else
      to_a[i]
    end
  end

  def to_s #:nodoc:
    to_a.to_s
  end
end

module XML::SiblingEnum
  private 
  
  # Iterates nodes and attributes
  def siblings(node, &blk)
    if n = node
      loop do
        blk.call(n)
        break unless n = n.next
      end
    end 
  end
end

class XML::Node
  include XML::SiblingEnum
  include Enumerable
  include Comparable
  
  # maybe these don't belong on all nodes...
  def each_child(&blk)
    siblings(child, &blk)   
  end

  def each_attr(&blk)
    siblings(properties, &blk)
  end

  # all siblings INCLUDING self
  def each_sibling(&blk)
    siblings(self, &blk)
  end
  
  # I guess this is what you'd expect?
  alias :each :each_child

  def to_a
    inject([]) { |ary,n| ary << n }
  end
  
  def <=>(other)
    to_s <=> other.to_s
  end  
end

class XML::Attr 
  include XML::SiblingEnum
  include Enumerable

  def each_sibling(&blk)
    siblings(self,&blk)
  end
  
  alias :each_attr :each_sibling
  alias :each :each_sibling
  
  def to_h
    inject({}) do |h,a| h[a.name] = a.value end
  end

  def to_a
    inject([]) do |ary,a| ary << [a.name, a.value] end
  end
  
  def to_s
    "#{name} = #{value}"
  end
end
