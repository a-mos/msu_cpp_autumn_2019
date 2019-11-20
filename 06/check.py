import subprocess

def check(expr, result):
    out = subprocess.run(['./tests', expr], stdout = subprocess.PIPE)
    if out.stdout.decode('ascii') != result:
        print('error, got {0}'.format(out.stdout))
    else:
    	print('pass')

check('1', '1done\n')
check('2', 'one+one = 2done\n')
check('3', 'one+onedone\n')
check('4', 'errdone\n')
check('5', 'errdone\n')
check('6', 'errdone\n')
check('7', '777onetwo3done\n')
check('8', 'errdone\n')
