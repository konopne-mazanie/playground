use strict;
use warnings;
use v5.12;

use DBI;

sub main {
    my $db = "users";
    my $host = "localhost";
    my $port = "3306";
    my $database = DBI->connect("DBI:mysql:database=$db;host=$host;port=$port","root","mysql") or die "Unable to connect";

    get_passwords($database);

    insert_user($database, "test2", "test2pwd");
    get_passwords($database);

    update_user($database, "test2", "test2pwd_new");
    get_passwords($database);

    remove_user($database, "test2");
    get_passwords($database);

    $database->disconnect();
}

sub get_passwords {
    my $database = shift;
    my $command = <<EOF;
        SELECT id, name, password
        FROM passwords
EOF
    my $query = run_query($database, $command);
    my ($id, $name, $password);

    while (($id, $name, $password) = $query->fetchrow()) {
        print "$id $name $password \n";
    }

    print "_________________________\n";
    $query->finish();
}

sub update_user {
    my $database = shift;
    my $user_name = shift;
    my $user_pass_new = shift;
    my $command = <<EOF;
        UPDATE passwords
        SET password = ?
        WHERE name = ?
EOF
    my $query = run_query($database, $command, [$user_pass_new, $user_name]);
    $query->finish();
}

sub remove_user {
    my $database = shift;
    my $user_name = shift;

    my $command = <<EOF;
        DELETE FROM passwords
        WHERE name = ?
EOF
    my $query = run_query($database, $command, [$user_name]);
    $query->finish();
}

sub insert_user {
    my $database = shift;
    my $user_name = shift;
    my $user_pass = shift;
    my $command = <<EOF;
        INSERT INTO passwords(name, password)
        VALUES(?, ?)
EOF
    my $query = run_query($database, $command, [$user_name, $user_pass]);
    $query->finish();
}

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

main();