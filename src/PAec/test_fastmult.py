#*******************************************************************************
 # Name        : test_fastmult.py
 # Author      : John Graham
 # Date        : 11/10/22
 # Description : Python test script for fastmult.cpp
#******************************************************************************/
"""
HOW TO USE THIS TEST SCRIPT
1.) Install Python on Ubuntu VM: 'sudo apt install python3'
2.) Alter your makefile by changing the '-g' flag to be '-O3' (to optimize for time)
3.) Have this script, fastmult.cpp, large_numbers.csv, and the makefile in their own directory
4.) Enter 'make' into the command line (in the same directory as your code)
5.) Enter 'python3 test_fastmult.py' into the command line
"""

import unittest
import subprocess
import csv
import time

class testFastMult(unittest.TestCase):
    def test1(self):
        '''testing 0*0 (should be a single 0)'''
        result=subprocess.run(["./fastmult", "0", "0"], check=True, capture_output=True)
        exp=ANSI.color_text(32)+str(b"0\n")+ANSI.color_text(37)
        rec=ANSI.color_text(31)+str(result.stdout)+ANSI.color_text(37)
        errmsg="Expected: "+exp+", Received: "+rec
        self.assertEqual(result.stdout, b"0\n", errmsg)
    def test2(self):
        '''testing 1*0 (should be a single 0)'''
        result=subprocess.run(["./fastmult", "1", "0"], check=True, capture_output=True)
        exp=ANSI.color_text(32)+str(b"0\n")+ANSI.color_text(37)
        rec=ANSI.color_text(31)+str(result.stdout)+ANSI.color_text(37)
        errmsg="Expected: "+exp+", Received: "+rec
        self.assertEqual(result.stdout, b"0\n", errmsg)
    def test3(self):
        '''testing 0*1 (should be a single 0)'''
        result=subprocess.run(["./fastmult", "0", "1"], check=True, capture_output=True)
        exp=ANSI.color_text(32)+str(b"0\n")+ANSI.color_text(37)
        rec=ANSI.color_text(31)+str(result.stdout)+ANSI.color_text(37)
        errmsg="Expected: "+exp+", Received: "+rec
        self.assertEqual(result.stdout, b"0\n", errmsg)
    def test4(self):
        '''testing 1*1 (should be 1)'''
        result=subprocess.run(["./fastmult", "1", "1"], check=True, capture_output=True)
        exp=ANSI.color_text(32)+str(b"1\n")+ANSI.color_text(37)
        rec=ANSI.color_text(31)+str(result.stdout)+ANSI.color_text(37)
        errmsg="Expected: "+exp+", Received: "+rec
        self.assertEqual(result.stdout, b"1\n", errmsg)
    def test5(self):
        '''testing single digit multiplication of identical numbers with a single digit result'''
        result=subprocess.run(["./fastmult", "2", "2"], check=True, capture_output=True)
        exp=ANSI.color_text(32)+str(b"4\n")+ANSI.color_text(37)
        rec=ANSI.color_text(31)+str(result.stdout)+ANSI.color_text(37)
        errmsg="Expected: "+exp+", Received: "+rec
        self.assertEqual(result.stdout, b"4\n", errmsg)
    def test6(self):
        '''testing single digit multiplication of different numbers with a single digit result'''
        result=subprocess.run(["./fastmult", "2", "3"], check=True, capture_output=True)
        exp=ANSI.color_text(32)+str(b"6\n")+ANSI.color_text(37)
        rec=ANSI.color_text(31)+str(result.stdout)+ANSI.color_text(37)
        errmsg="Expected: "+exp+", Received: "+rec
        self.assertEqual(result.stdout, b"6\n", errmsg)
    def test7(self):
        '''testing single digit multiplication with a more than single digit result'''
        result=subprocess.run(["./fastmult", "2", "6"], check=True, capture_output=True)
        exp=ANSI.color_text(32)+str(b"12\n")+ANSI.color_text(37)
        rec=ANSI.color_text(31)+str(result.stdout)+ANSI.color_text(37)
        errmsg="Expected: "+exp+", Received: "+rec
        self.assertEqual(result.stdout, b"12\n", errmsg)
    def test8(self):
        '''testing multiplication of more than one digit'''
        result=subprocess.run(["./fastmult", "10", "10"], check=True, capture_output=True)
        exp=ANSI.color_text(32)+str(b"100\n")+ANSI.color_text(37)
        rec=ANSI.color_text(31)+str(result.stdout)+ANSI.color_text(37)
        errmsg="Expected: "+exp+", Received: "+rec
        self.assertEqual(result.stdout, b"100\n", errmsg)
    def test9(self):
        '''testing multiplication of inputs with different numbers of digits'''
        result=subprocess.run(["./fastmult", "100", "10"], check=True, capture_output=True)
        exp=ANSI.color_text(32)+str(b"1000\n")+ANSI.color_text(37)
        rec=ANSI.color_text(31)+str(result.stdout)+ANSI.color_text(37)
        errmsg="Expected: "+exp+", Received: "+rec
        self.assertEqual(result.stdout, b"1000\n", errmsg)
    def test10(self):
        '''testing multiplication with larger results'''
        result=subprocess.run(["./fastmult", "34", "35"], check=True, capture_output=True)
        exp=ANSI.color_text(32)+str(b"1190\n")+ANSI.color_text(37)
        rec=ANSI.color_text(31)+str(result.stdout)+ANSI.color_text(37)
        errmsg="Expected: "+exp+", Received: "+rec
        self.assertEqual(result.stdout, b"1190\n", errmsg)
    def test11(self):
        '''testing that changing the order of the inputs doesn't matter'''
        result=subprocess.run(["./fastmult", "35", "34"], check=True, capture_output=True)
        exp=ANSI.color_text(32)+str(b"1190\n")+ANSI.color_text(37)
        rec=ANSI.color_text(31)+str(result.stdout)+ANSI.color_text(37)
        errmsg="Expected: "+exp+", Received: "+rec
        self.assertEqual(result.stdout, b"1190\n", errmsg)
    def test12(self):
        '''testing that padding 0's doesn't matter'''
        result=subprocess.run(["./fastmult", "00034", "000000035"], check=True, capture_output=True)
        exp=ANSI.color_text(32)+str(b"1190\n")+ANSI.color_text(37)
        rec=ANSI.color_text(31)+str(result.stdout)+ANSI.color_text(37)
        errmsg="Expected: "+exp+", Received: "+rec
        self.assertEqual(result.stdout, b"1190\n", errmsg)
    def test13(self):
        '''testing that different padding's don't matter'''
        result=subprocess.run(["./fastmult", "34", "0000000000000000000035"], check=True, capture_output=True)
        exp=ANSI.color_text(32)+str(b"1190\n")+ANSI.color_text(37)
        rec=ANSI.color_text(31)+str(result.stdout)+ANSI.color_text(37)
        errmsg="Expected: "+exp+", Received: "+rec
        self.assertEqual(result.stdout, b"1190\n", errmsg)
    def test14(self):
        '''testing larger inputs and results'''
        result=subprocess.run(["./fastmult", "2205", "1132"], check=True, capture_output=True)
        exp=ANSI.color_text(32)+str(b"2496060\n")+ANSI.color_text(37)
        rec=ANSI.color_text(31)+str(result.stdout)+ANSI.color_text(37)
        errmsg="Expected: "+exp+", Received: "+rec
        self.assertEqual(result.stdout, b"2496060\n", errmsg)
    def test15(self):
        '''testing larger inputs and results'''
        result=subprocess.run(["./fastmult", "2351", "1234"], check=True, capture_output=True)
        exp=ANSI.color_text(32)+str(b"2901134\n")+ANSI.color_text(37)
        rec=ANSI.color_text(31)+str(result.stdout)+ANSI.color_text(37)
        errmsg="Expected: "+exp+", Received: "+rec
        self.assertEqual(result.stdout, b"2901134\n", errmsg)
    def test16(self):
        '''lol nice'''
        result=subprocess.run(["./fastmult", "69420", "404"], check=True, capture_output=True)
        exp=ANSI.color_text(32)+str(b"28045680\n")+ANSI.color_text(37)
        rec=ANSI.color_text(31)+str(result.stdout)+ANSI.color_text(37)
        errmsg="Expected: "+exp+", Received: "+rec
        self.assertEqual(result.stdout, b"28045680\n", errmsg)
    def test17(self):
        '''testing very very large numbers'''
        n1=2**5000
        n2=2**5000
        nx=n1*n2
        result=subprocess.run(["./fastmult", str(n1), str(n2)], check=True, capture_output=True)
        errmsg=ANSI.color_text(31)+"Expected a different result (too large to display)"+ANSI.color_text(37)
        self.assertEqual(int(result.stdout), nx, errmsg)
    def test18(self):
        '''testing multiplication of 2 1000 digit numbers'''
        with open('large_numbers.csv', newline = '') as file:
            reader = csv.reader(file, quoting = csv.QUOTE_ALL, delimiter = ' ')
            large_numbers=[]
            for row in reader:
                large_numbers.append(row[0])
        result=subprocess.run(["./fastmult", large_numbers[0], large_numbers[1]], check=True, capture_output=True)
        errmsg=ANSI.color_text(31)+"Expected a different result (too large to display)"+ANSI.color_text(37)
        mult=int(large_numbers[0]) * int(large_numbers[1])
        self.assertEqual(int(result.stdout), mult, errmsg)
    def test19(self):
        '''ensures that 1000-digit multiplication can be done in under 1 second (be sure to set flags to -O3!)'''
        start_time=time.time()

        with open('large_numbers.csv', newline = '') as file:
            reader = csv.reader(file, quoting = csv.QUOTE_ALL, delimiter = ' ')
            large_numbers=[]
            for row in reader:
                large_numbers.append(row[0])
        result=subprocess.run(["./fastmult", large_numbers[0], large_numbers[1]], check=True, capture_output=True)
        errmsg1=ANSI.color_text(31)+"Expected a different result (too large to display)"+ANSI.color_text(37)
        mult=int(large_numbers[0]) * int(large_numbers[1])
        self.assertEqual(int(result.stdout), mult, errmsg1)

        end_time=time.time()
        exp=ANSI.color_text(32)+str(1)+" second"+ANSI.color_text(37)
        rec=ANSI.color_text(31)+str(end_time-start_time)+" seconds"+ANSI.color_text(37)
        errmsg2="Limit: "+exp+", Elapsed: "+rec
        self.assertLessEqual(end_time-start_time, 1, errmsg2) #1000 digit * 1000 digit should take < 1 second
    def test20(self):
        '''testing multiplication of 2 50,000 digit multiplication (this might take a while!)'''
        start_time=time.time()

        n1=2**166100 #this has 50,002 digits (a little above the maximum input)
        nx=n1**2
        result=subprocess.run(["./fastmult", str(n1), str(n1)], check=True, capture_output=True)
        errmsg=ANSI.color_text(31)+"Expected a different result (too large to display)"+ANSI.color_text(37)
        self.assertEqual(int(result.stdout), nx, errmsg)

        end_time=time.time()
        exp=ANSI.color_text(32)+str(30)+" seconds"+ANSI.color_text(37)
        rec=ANSI.color_text(31)+str(end_time-start_time)+" seconds"+ANSI.color_text(37)
        errmsg2="Limit: "+exp+", Elapsed: "+rec
        self.assertLessEqual(end_time-start_time, 30, errmsg2) #50000 digit * 50000 digit should take < 30 seconds




class ANSI():
    def color_text(code):
        return "\33[{code}m".format(code=code)




if __name__ == "__main__":
    unittest.main()