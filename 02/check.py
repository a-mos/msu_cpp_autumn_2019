import subprocess

def check(expr, result):
    out = subprocess.run(['./alloc', *expr], stdout = subprocess.PIPE)
    if out.stdout.decode('ascii') != result:
        print('error, got {0}'.format(out.stdout))
    else:
    	print('pass')

check('', 'No input\n')
check(['100', 'maxsize'], 'Max size: 100\n')
check(['100', 'alloc100'], 'Allocated: 100\n')
check(['100', 'alloc101'], 'Not allocated: 101\n')
check(['100', 'alloc-1'], 'Not allocated: -1\n')

check(['100', 'alloc10', 'cursize', 'alloc30', 'cursize', 'alloc100'], \
      'Allocated: 10\nCur size: 10\nAllocated: 30\nCur size: 40\nNot allocated: 100\n')

check(['100', 'alloc100', 'cursize', 'alloc100', 'reset', 'alloc100'], \
      'Allocated: 100\nCur size: 100\nNot allocated: 100\nReset\nAllocated: 100\n')

check(['100', 'alloc50', 'alloc50', 'alloc1', 'cursize'], \
      'Allocated: 50\nAllocated: 50\nNot allocated: 1\nCur size: 100\n')

check(['100', 'maxsize', 'alloc100', 'reset', 'alloc200', 'reset', 'alloc100', 'cursize'], \
      'Max size: 100\nAllocated: 100\nReset\nNot allocated: 200\nReset\nAllocated: 100\nCur size: 100\n')
