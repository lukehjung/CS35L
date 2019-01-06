#!/usr/bin/python

"""
Luke Jung
CS 35L Fall
904-982-644

Adapted from randline.py from Eggert
"""

import random, sys
from optparse import OptionParser

class randline:
    def __init__(self, filename):
        f = open(filename, 'r')
        self.lines = f.readlines()
        self.len = len(self.lines)
        f.close()
    def sample(self, count):
        j = random.sample(self.lines, count)
        for index in range(count):
            sys.stdout.write(j[index])
        return 0
    def write_repeat(self, count):
        for index in range(count):
            sys.stdout.write(random.choice(self.lines))
        return 0
    def repeat(self):
        while True :
            sys.stdout.write(random.choice(self.lines))
        return 0
    def filelength(self):
        return self.len

def main():
    version_msg = "%prog 2.0"
    usage_msg = """%prog [OPTION]... FILE

Output randomly selected lines from FILE."""

    input_range = False
    output_range = False
    numlines = 0    

    parser = OptionParser(version=version_msg,
                          usage=usage_msg)

    parser.add_option("-n", "--numlines",
                      action="store", dest="numlines", default=1, 
                      help="output NUMLINES lines (default 1)")

    parser.add_option("-i", "--input-range",
                      action="store", dest="range", 
                    help="treat each number LO through HI as input line")

    parser.add_option("-r", "--repeat", action="store_true", dest="repeat", default=False,
    				help="output ines can be repeated")

    options, args = parser.parse_args(sys.argv[1:])

    try:
        numlines = int(options.numlines)
        if numlines > 1:
            output_range = True
        strrange = options.range
        if strrange is not None:
            input_range = True
    except:
        parser.error("invalid NUMLINES: {0}".
                     format(options.numlines))
    if numlines < 0:
        parser.error("negative count: {0}".
                     format(numlines))
    if not input_range:
        if len(args) != 1:
            parser.error("wrong number of operands")
        input_file = args[0]
        generator = randline(input_file)
        lo_input = 0
        hi_input = generator.filelength()

    try:
        if int(options.repeat) and not input_range:
            if output_range:
                generator.write_repeat(numlines)
            else:
                generator.repeat()
        if input_range:
            if len(args) >= 1:
                parser.error("wrong number of operands")
            indexlist = strrange.split("-")
            lo_input = int(indexlist[0])
            hi_input = int(indexlist[1])
            count = hi_input-lo_input
            items = list(range(lo_input,hi_input+1))
            random.shuffle(items)
         
            if int(options.repeat):
                if output_range:
                    for index in range(numlines):
                        print(random.choice(items))
                else:
                    while True:
                        print(random.choice(items))
            if output_range and not options.repeat:
	            if hi_input <= numlines:
	                numlines = hi_input
	            for index in range(numlines):
                     print(items[index])
            if not output_range and not options.repeat:
                for index in range(count+1):
                    print(items[index])
        else:
            if hi_input <= numlines:
                numlines = hi_input
            generator.sample(numlines)

    except IOError as err:
        sys.parser.error("I/O error({0}): {1}".
                     format(errno, strerror))

if __name__ == "__main__":
    main()