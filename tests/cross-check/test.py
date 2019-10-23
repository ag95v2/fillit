#!/bin/python

import os
import sys
import glob
import time
import argparse

print('\x1b[0;31;40m' + 'How about some colored print???' + '\x1b[0m')

parser = argparse.ArgumentParser()
parser.add_argument('--n_tetr',  help='Numbers of tetraminos each experiment')
parser.add_argument('--n_tests', help='Number of experiments')

#sys.argv includes a list of elements starting with the program
if len(sys.argv) < 2:
    parser.print_usage()
    sys.exit(1)

args = parser.parse_args()

n_tests = args.n_tests
n_tetr = args.n_tetr


old_dir = os.getcwd()
dirs = glob.glob(old_dir + '/*/')

for d in dirs:
    os.chdir(d)
    print("Making a binary from: {}".format(os.getcwd()))
    os.system("make re")
    name = 'fillit_' + d.split('/')[-2] 
    os.system("mv fillit {}/{}".format(old_dir, name))

os.chdir(old_dir)

os.chdir('../random_input_generator/')
os.system("make ")
os.system("mv random_input_generator {}/random_input_generator".format(old_dir))
os.chdir(old_dir)

print("Making our binary")
os.chdir('../../')
os.system("make ")
os.system("cp fillit {}/fillit_our".format(old_dir))
os.chdir(old_dir)

fillit_binaries = [i for i in filter (lambda x: "fillit" in x, os.listdir())]

print('\x1b[0;32;40m' +"*" * 80+ '\x1b[0m')
print('\x1b[0;32;40m' + "Compilation finished"+ '\x1b[0m')
print('\x1b[0;32;40m' + "Got following binaries: " + str(fillit_binaries)+ '\x1b[0m')

print('\x1b[0;32;40m' +"*" * 80+ '\x1b[0m')

def gen_rnd_input(n_tetr):
    os.system("./random_input_generator {} > input.txt".format(n_tetr))

performance_summary = dict()
for name in fillit_binaries:
    performance_summary[name] = 0

def run_test(n_tetr):
    gen_rnd_input(n_tetr)

    for name in fillit_binaries:
        start = time.time()
        os.system("./{} input.txt > output_{}.txt".format(name, name.split('_')[-1]))
        end = time.time()
        performance_summary[name] += end - start

    exit_flag = 0
    for name in fillit_binaries:
        short = name.split('_')[-1]
        out = os.popen('diff output_{}.txt output_our.txt'.format(short)).read()
        if (len(out) > 0):
            print('\x1b[7;31;40m' +"Our and {}'s output differ".format(short)+ '\x1b[0m')
            exit_flag = 1
    
    if (exit_flag == 1):
        print('\x1b[0;32;40m' +'*' * 80+ '\x1b[0m')
        print('\x1b[0;31;40m' +"We found a bug, congrats."+ '\x1b[0m')
        print('\x1b[0;31;40m' +"Look at input and output of aforementioned programs."+ '\x1b[0m')
        print('\x1b[0;31;40m' +"Terminating script, doing performance dump at performance_summary.txt"+ '\x1b[0m')
        print(performance_summary,file= open("performance_summary.txt", "w"))
        sys.exit()

def run_n_tests(n_tetr, n_tests):
    '''
        Run n_tests random experinents
    '''
    for i in range(n_tests):
        run_test(n_tetr)
        
    print('\x1b[0;32;40m' +"All {} tests passed!".format(n_tests)+ '\x1b[0m')
    print('\x1b[0;32;40m' +"Performance summary:"+ '\x1b[0m')
    print(performance_summary)

print('\x1b[0;32;40m' +"Running {} random  tests with {} tetraminos".format(n_tests, n_tetr))
print('\x1b[0;32;40m' +'*' * 80+ '\x1b[0m')
run_n_tests(int(n_tetr), int(n_tests))
