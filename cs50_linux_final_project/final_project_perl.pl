#!/usr/bin/perl

open (FILE, '<', "data/usrAccounts/$ARGV[0].csv");
print <FILE>;
print "\n";
close (FILE);
