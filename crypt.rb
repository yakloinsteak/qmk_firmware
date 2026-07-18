#!/usr/bin/env ruby

require 'securerandom'

def goat(y)
  y.map { |x| '0b'+x.to_s(2) }.join(',')
end

cleartext = ENV['WORD'] + "\0"
key = cleartext.length.times.map do
  SecureRandom.bytes(1).bytes[0]
end

print 'static char cleartext[] = {'
print goat(cleartext.bytes)
puts '};'

print 'static char key[] = {'
print goat(key)
puts '};'

print 'static char cyphertext[] = {'
cyphertext = cleartext.bytes.map.with_index { |x,i| val = x ^ key[i] }
print goat(cyphertext)
puts '};'
