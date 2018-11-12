package my_database;

use strict;
use warnings;
use v5.12;

use DBI;

### Static (class) methods
sub connect {
	my ($class, $db, $host, $port) = @_;
	DBI->connect("DBI:mysql:database=$db;host=$host;port=$port","root","mysql") or die "Unable to connect";
}

sub new {
    my ($class, $database, $table) = @_;
    my $self = bless {
        database   =>  $database,
        table	   =>  $table
    }, $class;
}

### Methods

sub get_passwords {
	my $self = shift;
    my $database = $self->{database};
	my $table = $self->{table};
    my $command = <<EOF;
        SELECT id, name, password
        FROM $table
EOF

    my $query = run_query($database, $command);
    my ($id, $name, $password);
	my @passwords;

    while (($id, $name, $password) = $query->fetchrow()) {
		my @line = ($name, $password);
		push @passwords, \@line;
    }
    $query->finish();
	@passwords;
}

sub update_user {
	my ($self, $user_name, $user_pass_new) = @_;
    my $database = $self->{database};
	my $table = $self->{table};

    my $command = <<EOF;
        UPDATE $table
        SET password = ?
        WHERE name = ?
EOF
    my $query = run_query($database, $command, [$user_pass_new, $user_name]);
    $query->finish();
}

sub remove_user {
    my ($self, $user_name) = @_;
    my $database = $self->{database};
	my $table = $self->{table};

    my $command = <<EOF;
        DELETE FROM $table
        WHERE name = ?
EOF
    my $query = run_query($database, $command, [$user_name]);
    $query->finish();
}

sub insert_user {
    my ($self, $user_name, $user_pass) = @_;
    my $database = $self->{database};
	my $table = $self->{table};

    my $command = <<EOF;
        INSERT INTO $table(name, password)
        VALUES(?, ?)
EOF
    my $query = run_query($database, $command, [$user_name, $user_pass]);
    $query->finish();
}

### private

sub run_query {
    my $database = shift;
    my $query = shift;
    my $params = shift;

    my $prep = $database->prepare($query) or die "bad statement";
    if (defined $params) {
        $prep->execute(@$params) or die "unable to execute query";
    } else {
        $prep->execute() or die "unable to execute query";
    }
    $prep;
}

sub DESTROY {
	my $self = shift;
	my $database = $self->{database};
	$database->disconnect();
}

1;
