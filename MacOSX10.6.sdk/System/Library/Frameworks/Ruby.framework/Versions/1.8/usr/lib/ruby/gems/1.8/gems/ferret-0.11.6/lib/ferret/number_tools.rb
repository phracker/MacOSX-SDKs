require 'date'
require 'time'

class Float
  # Return true if the float is within +precision+ of the other value +o+. This
  # is used to accommodate for floating point errors.
  #
  # o::         value to compare with
  # precision:: the precision to use in the comparison.
  # return::    true if the match is within +precision+
  def =~(o, precision = 0.0000000001)
    return (1 - self/o).abs < precision
  end
end

# Provides support for converting integers to Strings, and back again. The
# strings are structured so that lexicographic sorting order is preserved.
# 
# That is, if integer1 is less than integer2 for any two integers integer1 and
# integer2, then integer1.to_s_lex is lexicographically less than
# integer2.to_s_lex. (Similarly for "greater than" and "equals".)
#
# This class handles numbers between - 10 ** 10,000 and 10 ** 10,000
# which should cover all practical numbers. If you need bigger numbers,
# increase Integer::LEN_STR_SIZE.
class Integer
  # LEN_SIZE of 4 should handle most numbers that can practically be held in
  # memory.
  LEN_STR_SIZE = 4
  NEG_LEN_MASK = 10 ** LEN_STR_SIZE
  LEN_STR_TEMPLATE = "%0#{LEN_STR_SIZE}d"

  # Convert the number to a lexicographically sortable string. This string will
  # use printable characters only but will not be human readable.
  def to_s_lex
    if (self >= 0)
      num_str = self.to_s
      len_str = LEN_STR_TEMPLATE % num_str.size
      return len_str + num_str
    else
      num = self * -1
      num_str = num.to_s
      num_len = num_str.size
      len_str = LEN_STR_TEMPLATE % (NEG_LEN_MASK - num_len)
      num = (10 ** num_str.size) - num
      return "-#{len_str}%0#{num_len}d" % num
    end
  end

  # Convert the number to a lexicographically sortable string by padding with
  # 0s. You should make sure that you set the width to a number large enough to
  # accommodate all possible values. Also note that this method will not work
  # with negative numbers. That is negative numbers will sort in the opposite
  # direction as positive numbers. If you have very large numbers or a mix of
  # positive and negative numbers you should use the Integer#to_s_lex method
  #
  # width::  number of characters in the string returned. Default is 10. So
  #          123.to_s_pad(5) => 00123 and -123.to_s_pad(5) => -0123
  # return:: padding string representation of the number.
  def to_s_pad(width = 10)
    "%#{width}d" % self
  end
end

class Date
  # Convert the Date to a lexicographically sortable string with the required
  # precision. The format used is %Y%m%d
  #
  # precision:: the precision required in the string version of the date. The
  #             options are :year, :month and :day
  # return::    a lexicographically sortable string representing the date
  def to_s_lex(precision = :day)
    self.strftime(Time::LEX_FORMAT[precision])
  end
end

class DateTime
  # Convert the DateTime to a lexicographically sortable string with the
  # required precision. The format used is %Y%m%d %H:%M:%S.
  #
  # precision:: the precision required in the string version of the date. The
  #             options are :year, :month, :day, :hour, :minute and :second
  # return::    a lexicographically sortable string representing the date
  def to_s_lex(precision = :day)
    self.strftime(Time::LEX_FORMAT[precision])
  end
end

class Time
  LEX_FORMAT = {
      :year        => "%Y",
      :month       => "%Y-%m",
      :day         => "%Y-%m-%d",
      :hour        => "%Y-%m-%d %H",
      :minute      => "%Y-%m-%d %H:%M",
      :second      => "%Y-%m-%d %H:%M:%S",
      :millisecond => "%Y-%m-%d %H:%M:%S"
  }

  # Convert the Time to a lexicographically sortable string with the required
  # precision. The format used is %Y%m%d %H:%M:%S.
  #
  # precision:: the precision required in the string version of the time. The
  #             options are :year, :month, :day, :hour, :minute and :second
  # return::    a lexicographically sortable string representing the date
  def to_s_lex(precision = :day)
    self.strftime(LEX_FORMAT[precision])
  end
end

class String
  # Convert a string to an integer. This method will only work on strings that
  # were previously created with Integer#to_s_lex, otherwise the result will be
  # unpredictable.
  def to_i_lex
    if (self[0] == ?-)
      return self[(Integer::LEN_STR_SIZE + 1)..-1].to_i -
        10 ** (self.size - Integer::LEN_STR_SIZE - 1)
    else
      return self[Integer::LEN_STR_SIZE..-1].to_i
    end
  end

  # Convert a string to a Time. This method will only work on strings that
  # match the format %Y%m%d %H%M%S, otherwise the result will be unpredictable.
  def to_time_lex
    vals = []
    self.gsub(/(?:^|[- :])(\d+)/) {vals << $1.to_i; $&}
    Time.mktime(*vals)
  end

  # Convert a string to a Date. This method will only work on strings that
  # match the format %Y%m%d %H%M%S, otherwise the result will be unpredictable.
  def to_date_lex
    return Date.strptime(self + "-02-01", "%Y-%m-%d")
  end

  # Convert a string to a DateTime. This method will only work on strings that
  # match the format %Y%m%d %H%M%S, otherwise the result will be unpredictable.
  def to_date_time_lex
    return DateTime.strptime(self + "-01-01", "%Y-%m-%d %H:%M:%S")
  end

  private
  
  def get_lex_format(len)
    case len
    when  0.. 3: ""
    when  4.. 5: "%Y"
    when  6.. 7: "%Y%m"
    when  8.. 9: "%Y%m%d"
    when 10..11: "%Y%m%d%H"
    when 12..13: "%Y%m%d%H%M"
    else "%Y%m%d%H%M%S"
    end
  end
end
