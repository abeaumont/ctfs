def flag_gen(alpha):
	import hashlib
	return 'SharifCTF{%s}' % hashlib.md5(str(alpha).encode()).hexdigest()

alpha = # Find alpha, and set it here!
print(flag_gen(alpha))
