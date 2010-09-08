#!/usr/bin/perl
use warnings;
use strict;

my $thePath = $ARGV[0];
print("$thePath");

sleep(1);
chdir("$thePath");
system("xterm -hold -C -e ./SoundClient");
