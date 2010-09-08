#!/usr/bin/perl
use warnings;
use strict;

my $thePath = $ARGV[1];
print("$thePath");

sleep(1);
chdir("$thePath");
system("xterm -C -e ./SoundClient");
