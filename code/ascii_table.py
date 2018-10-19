def escape(c: chr) :
    if c in ['&', '%', '$', '#', '_', '{', '}', '~', '^', '\\']:
        return f'\\{c}'
    return c


for x in range(32,127):
    print("%d & %s \\\\" % (x, escape(chr(x))))
