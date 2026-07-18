#!/usr/bin/env ruby

require 'securerandom'

def goat(y)
  y.map { |x| '0x'+x.to_s(16) }.join(',')
end

cleartext = ENV['WORD'] + "\0"
key = cleartext.length.times.map do
  SecureRandom.bytes(1).bytes[0]
end

print '#define CLEARTEXT {'
print goat(cleartext.bytes)
puts "}"

print '#define KEY {'
print  goat(key)
puts "}"

print '#define CYPHERTEXT {'
cyphertext = cleartext.bytes.map.with_index { |x,i| val = x ^ key[i] }
print goat(cyphertext)
puts "}"
