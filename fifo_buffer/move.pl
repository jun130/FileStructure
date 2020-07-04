#!/usr/local/bin/perl

LOOP: while (1){
	$a = shift();
	if ($a eq "") {last LOOP;}
	$a =~ /(.*)\.(.*)$/;
	$b = $1 . ".cpp";
	$line .= "mv $a $b; ";
	#print "next $line\n";
}
print "line: $line\n";
exec($line);
