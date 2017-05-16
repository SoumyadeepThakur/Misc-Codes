# The following code snippet tries to figure out the randomness in the bytes obtained from 
# an RC4 stream cipher 

import numpy as np
import sys
import struct

def key_scheduling(key, key_length):
	s = [x for x in range(256)]
	state = np.array(s,dtype=np.int16)
	j = 0
	for i in range(256):
		j = (j+state[i]+key[i%key_length])%256
		state[i],state[j] = state[j],state[i]
	return state

def prga(i, j, state):
	i = (i+1)%256
	j = (j+state[i])%256
	state[i],state[j] = state[j],state[i]
	index = (state[i]+state[j])%256
	return (i,j,index)

if __name__ == '__main__':

	freq=np.zeros((5,256),dtype=np.uint8)
	for j in range(100000):
		secret_key = np.array(struct.unpack('4B' , struct.pack('>I',j)))
		cur_state = key_scheduling(secret_key,secret_key.size)
		x,y = 0,0
		for i in xrange(5):
			x,y,next_byte=prga(x,y,cur_state)
			freq[i][next_byte]=freq[i][next_byte]+1
		if j % 10000 == 0:
			print 'batch'

	np.savetxt('freq_data.txt',freq,'%d') # store freq for 1st 5 bits
	print freq

