#!/usr/bin/perl
use strict;
use warnings;

use CGI ":standard";

use File::Basename qw(dirname);
use Cwd  qw(abs_path);
use lib dirname(dirname abs_path $0) . "/cgi-bin";


use my_database;

my $database_obj = my_database->new(my_database->connect("users", "localhost", "3306"), "passwords");

my $name = param("name"); 
my $pass = param("password");
#my ($name, $pass) = qw\abc def\;

$database_obj->insert_user($name, $pass);
$database_obj->remove_user($name);


print "Content-type: text/html\n\n";
print "<html> <head>\n";
print "<title>Register!</title>";
print "</head>\n";
print "<body>\n";
print "<h1>OK!</h1>\n";
print "</body> </html>\n";
