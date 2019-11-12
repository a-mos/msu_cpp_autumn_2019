import subprocess

def check(expr, result):
    out = subprocess.run(['./tests', expr], stdout = subprocess.PIPE)
    if out.stdout.decode('ascii') != result:
        print('error, got {0}'.format(out.stdout))
    else:
    	print('pass')

check('1', '1 true 2 \ndone\n')
check('2', 'done\n')
