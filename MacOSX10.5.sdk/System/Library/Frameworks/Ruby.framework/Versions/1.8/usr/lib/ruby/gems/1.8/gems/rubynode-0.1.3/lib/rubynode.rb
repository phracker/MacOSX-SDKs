
require "rubynode_ext"

class RubyNode

	VERSION = "0.1.3"

	NODE_ATTRIBS = {
		:alias        =>
			lambda { |node|
				{ # ruby >1.8.4 doesn't have nd_new and nd_old
					:new => ((node.respond_to?(:nd_new) && node.nd_new) || node.u1_node),
					:old => ((node.respond_to?(:nd_old) && node.nd_old) || node.u2_node),
				}
			},
		:alloca       => [], # not supported
		:and          => {:first=>:nd_1st, :second=>:nd_2nd},
		:args         => [:cnt, :rest, :opt],
		:argscat      => [:body, :head],
		:argspush     => [:body, :head],
		:array        => [:head, :alen, :next],
		:attrasgn     => [:mid, :args, :recv],
		:attrset      => [:vid],
		:back_ref     => [:nth, :cnt],
		:begin        => [:body],
		:block        => [:head, :next],
		:block_arg    => [:vid, :cnt],
		:block_pass   => [:body, :iter],
		:bmethod      => [:cval],
		:break        => [:stts],
		:call         => [:mid, :args, :recv],
		:case         => [:body, :head],
		:cdecl        => [:vid, :value, :else],
		:cfunc        => [:argc, :cfnc],
		:class        => [:super, :cpath, :body],
		:colon2       => [:head, :mid],
		:colon3       => [:mid],
		:const        => [:vid],
		:cref         => [:next, :clss],
		:cvar         => [:vid],
		:cvasgn       => [:vid, :value],
		:cvdecl       => [:vid, :value],
		:dasgn        => [:vid, :value],
		:dasgn_curr   => [:vid, :value],
		:defined      => [:head],
		:defn         => [:mid, :defn, :noex], # noex seems unused and always NOEX_PRIVATE in 1.8.4
		:defs         => [:mid, :defn, :recv],
		:dmethod      => [:cval],
		:dot2         => [:beg, :end],
		:dot3         => [:beg, :end],
		:dregx        => [:next, :lit, :cflag],
		:dregx_once   => [:next, :lit, :cflag],
		:dstr         => [:next, :lit],
		:dsym         => [:next, :lit],
		:dvar         => [:vid],
		:dxstr        => [:next, :lit],
		:ensure       => [:head, :ensr],
		:evstr        => [:body],
		:false        => [],
		:fbody        => [:orig, :mid, :head],
		:fcall        => [:mid, :args],
		:flip2        => [:cnt, :beg, :end],
		:flip3        => [:cnt, :beg, :end],
		:for          => [:body, :iter, :var],
		:gasgn        => [:vid, :value], # entry not supported
		:gvar         => [:vid], # entry not supported
		:hash         => [:head],
		:iasgn        => [:vid, :value],
		:if           => [:body, :cond, :else],
		:ifunc        => [:tval, :state, :cfnc],
		:iter         => [:body, :iter, :var],
		:ivar         => [:vid],
		:lasgn        => [:vid, :cnt, :value],
		:last         => [],
		:lit          => [:lit],
		:lvar         => [:vid, :cnt],
		:masgn        => [:head, :value, :args],
		:match        => [:lit],
		:match2       => [:value, :recv],
		:match3       => [:value, :recv],
		:memo         => {:u1_value=>:u1_value}, # different uses in enum.c, variabe.c and eval.c ...
		:method       => [:body, :noex, :cnt], # cnt seems to be always 0 in 1.8.4
		:module       => [:cpath, :body],
		:newline      => [:next],
		:next         => [:stts],
		:nil          => [],
		:not          => [:body],
		:nth_ref      => [:nth, :cnt],
		:op_asgn1     => [:mid, :args, :recv],
		:op_asgn2     =>
			lambda { |node|
				if ((v = node.nd_vid) && (m = node.nd_mid) && (a = node.nd_aid))
					{:vid => v, :mid => m, :aid => a}
				else
					{:recv => node.nd_recv, :value => node.nd_value, :next => node.nd_next}
				end
			},
		:op_asgn_and  => [:head, :value],
		:op_asgn_or   => [:head, :aid, :value],
		:opt_n        => [:body],
		:or           => {:first=>:nd_1st, :second=>:nd_2nd},
		:postexe      => [],
		:redo         => [],
		:resbody      => [:body, :head, :args],
		:rescue       => [:head, :else, :resq],
		:retry        => [],
		:return       => [:stts],
		:sclass       => [:recv, :body],
		:scope        => [:rval, :next, :tbl],
		:self         => [],
		:splat        => [:head],
		:str          => [:lit],
		:super        => [:args],
		:svalue       => [:head],
		:to_ary       => [:head],
		:true         => [],
		:undef        =>
			lambda { |node|
				# ruby >1.8.4 uses u2.node instead of nd_mid
				{:mid => (node.u2_node || node.nd_mid)}
			},
		:until        => [:body, :cond, :state],
		:valias       =>
			lambda { |node|
				{ # ruby >1.8.4 doesn't have nd_new and nd_old
					:new => ((node.respond_to?(:nd_new) && node.nd_new) || node.u1_id),
					:old => ((node.respond_to?(:nd_old) && node.nd_old) || node.u2_id),
				}
			},
		:vcall        => [:mid],
		:when         => [:body, :head, :next],
		:while        => [:body, :cond, :state],
		:xstr         => [:lit],
		:yield        => [:head, :state],
		:zarray       => [],
		:zsuper       => [],
	}
	if RUBY_VERSION >= "1.9.0"
		# nodes that are only in 1.9 or changed in 1.9
		NODE_ATTRIBS.merge!({
			:args         => [:frml, :rest, :opt, :head],
			:colon2       => [:head, :mid, :recv], # head is also accessed as recv in 1.9.0 ???
			:errinfo      => [],
			:lambda       => [:body, :var],
			:method       => [:body, :noex],
			:postexe      => [:body],
			:prelude      => [:body, :head],
			:values       => [:alen, :head, :next],
		})
	end

	def attribs_hash
		if (t = NODE_ATTRIBS[type])
			case t
			when Array
				res = {}
				t.each { |s| res[s] = send("nd_#{s}") }
				res
			when Hash
				res = {}
				t.each { |k, v| res[k] = send(v) }
				res
			else
				t.call(self)
			end
		else
			# guess by trying
			u1 = u1_value || u1_id || u1_tbl || u1_as_long
			u2 = u2_value || u2_id || u2_argc
			u3 = u3_value || u3_id || u3_cnt
			{:u1 => u1, :u2 => u2, :u3 => u3}
		end
	end

	def transform(opts = {})
		if type == :newline && !opts[:keep_newline_nodes]
			tmp = nd_next
			return tmp && tmp.transform(opts)
		end
		if (type == :array && !opts[:keep_array_nodes]) || (type == :block && !opts[:keep_block_nodes])
			arr = []
			tmp = self
			begin
				tmp_head = tmp.nd_head
				tmp_head = tmp_head.transform(opts) if RubyNode === tmp_head
				arr << tmp_head
			end while tmp = tmp.nd_next
			[type, arr]
		else
			ah = attribs_hash
			ah.each { |k, v|
				ah[k] = v.transform(opts) if RubyNode === v
			}
			ah[:node] = self if opts[:include_node]
			[type, ah]
		end
	end

	def inspect
		"#<#{self.class} #{type.inspect}>"
	end

	def to_s
		"#{self.class}(#{type.inspect}, #{attribs_hash.inspect})"
	end
end
