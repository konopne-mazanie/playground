package MyModuleInherited;

use strict;
use warnings;
use v5.12;

use File::Basename qw(dirname);
use Cwd  qw(abs_path);
use lib dirname(dirname abs_path $0) . "/perl";
use MyModule;
use MyClass;

use parent qw(MyClass);

1;