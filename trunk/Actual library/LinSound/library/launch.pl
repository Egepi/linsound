#!/usr/bin/perl
use warnings;
use strict;

my $thePath = $ARGV[0];
#my $thePort = $ARGV[1];

chdir("$thePath");
system("./SoundClient");
