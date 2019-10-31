import subprocess

def check(expr, result):
    out = subprocess.run(['./tests', expr], stdout = subprocess.PIPE)
    if out.stdout.decode('ascii') != result:
        print('error, got {0}'.format(out.stdout))
    else:
    	print('pass')

check('1', 'done\n')
check('2', 'done\n')
check('3', 'done\n')
check('4', 'done\n')
check('5', 'done\n')
check('6', 'done\n')
check('7', 'done\n')
check('8', 'out_of_range\ndone\n')
check('9', 'out_of_range\ndone\n')
check('10', 'out_of_range\ndone\n')
