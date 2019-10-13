import subprocess

def check(expr, result):
    out = subprocess.run(['./calc', expr], stdout = subprocess.PIPE)
    if out.stdout.decode('ascii') != result:
        print('error {0} != {1}, got {2}'.format(expr, result, out.stdout))
    else:
    	print('pass')
#Spaces
check('  1 			', '1\n')
check('    -	   3  ', '-3\n')
check('    -	-   - - - - - 3  ', '-3\n')

#Priority
check('2 + 2 * 2', '6\n')
check('6 / 2 / 2', '1\n')
check('6 /-2 / 2', '-1\n')
check('2 + -5 / -5  + 5', '8\n')
check('2 - -5 + -5  / 5', '6\n')
check('2 + 3 * 4 - -2', '16\n')
check('2 + 3 * -4 - --2', '-12\n')

#Invalid expression
check('', 'Invalid expression\n')
check('-', 'Invalid expression\n')
check('+', 'Invalid expression\n')
check('++5', 'Invalid expression\n')
check('+-5', 'Invalid expression\n')
check('-5+5*', 'Invalid expression\n')
check('2 + 2 +', 'Invalid expression\n')
check('2a + 2a', 'Invalid expression\n')
check('5 * 2 + 5 			a', 'Invalid expression\n')
check('5 *= 5', 'Invalid expression\n')
check('5 /* 1', 'Invalid expression\n')

#Div by zero
check('1 / 0', 'Division by zero\n')
check('0 / 0', 'Division by zero\n')

#All
check('100 * 2 - 524 + 541 * 59 - 4521 * -55 + 5241 * 10 / 2', '306455\n')
check(' -777 * -1337 + 1337 - 777 + 1337 - 1337 / 7 - 77', '1040478\n')
check(' 1 * 2 * 3 * 4 * 5 * 6 - -1 * -2 * -3 * -4 * -5 * -6', '0\n')