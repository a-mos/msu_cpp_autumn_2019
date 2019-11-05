import subprocess

def check(expr, result):
    out = subprocess.run(['./tests', expr], stdout = subprocess.PIPE)
    if out.stdout.decode('ascii') != result:
        print('error, got {0}'.format(out.stdout))
    else:
    	print('pass')

check('1', 'done\n')
check('2', 'done\n')
check('3', '18446744073709551614done\n')
check('4', '9223372036854775809done\n')
check('5', '-2done\n')
check('6', '0done\n')
check('7', 'done\n')
check('8', 'done\n')
check('9', 'done\n')
check('10', 'done\n')
check('11', '-4done\n')
