#!/usr/bin/perl
use strict;
use warnings FATAL => 'all';
use v5.12;

use File::Basename qw(dirname);
use Cwd  qw(abs_path);
use lib dirname(dirname abs_path $0) . "/cgi-bin";
use my_database;

use Data::Dumper;
use DBI;

sub get_passwords {
    my $db = shift;

    my $command = <<EOF;
        SELECT id, name, password
        FROM passwords
EOF

    my $query = my_database::run_query($db, $command);
    my ($id, $name, $password);
    my @passwords;

    while (($id, $name, $password) = $query->fetchrow()) {
        my @line = ($name, $password);
        push @passwords, \@line;
    }
    $query->finish();
    \@passwords;
}

sub get_passwords_ordered {
    my $db = shift;

    my $command = <<EOF;
        SELECT name
        FROM passwords
        ORDER BY name
EOF

    my $query = my_database::run_query($db, $command);
    my ($name);
    my @names;

    while (($name) = $query->fetchrow()) {
        push @names, $name;
    }
    $query->finish();
    \@names;
}

sub distinct_like_where {
    my $db = shift;

    my $command = <<EOF;
        SELECT DISTINCT filter.name
        FROM (
            SELECT id, name, password
            FROM passwords
            WHERE name like "test_" AND id BETWEEN 5 AND 6
        ) AS filter
EOF

    my $query = my_database::run_query($db, $command);
    my ($name);
    my @names;

    while (($name) = $query->fetchrow()) {
        push @names, $name;
    }
    $query->finish();
    \@names;
}

sub names_with_priviledges {
    my $db = shift;

    my $command = <<EOF;
        SELECT name
        FROM passwords
        WHERE id IN (
            SELECT id
            FROM priviledges
            WHERE access IN ("mid", "low")
        )
EOF

    my $query = my_database::run_query($db, $command);
    my ($name);
    my @names;

    while (($name) = $query->fetchrow()) {
        push @names, $name;
    }
    $query->finish();
    \@names;
}

sub priviledges_for_name {
    my $db = shift;

    my $command = <<EOF;
        SELECT name, access
        FROM passwords INNER JOIN priviledges ON passwords.id = priviledges.id
EOF

    my $query = my_database::run_query($db, $command);
    my ($name, $priv);
    my @names;

    while (($name, $priv) = $query->fetchrow()) {
        my @row = ($name, $priv);
        push @names, \@row;
    }
    $query->finish();
    \@names;
}

sub priviledges_and_last_entry_for_name { #prints date of the last access and priviledges for every audited user
    my $db = shift;

    my $command = <<EOF;
        SELECT name, access, last_entry
        FROM passwords AS pass CROSS JOIN priviledges AS priv CROSS JOIN audit AS au
        WHERE pass.id = au.id AND pass.id = priv.id
        ORDER BY last_entry DESC
        LIMIT 1
EOF

    my $query = my_database::run_query($db, $command);
    my ($name, $priv, $acc);
    my @names;

    while (($name, $priv, $acc) = $query->fetchrow()) {
        my @row = ($name, $priv, $acc);
        push @names, \@row;
    }
    $query->finish();
    \@names;
}

sub names_non_audited {
    my $db = shift;

    my $command = <<EOF;
        SELECT DISTINCT name
        FROM passwords LEFT JOIN audit USING (id)
        WHERE audit.id IS NULL
EOF

    my $query = my_database::run_query($db, $command);
    my ($name);
    my @names;

    while (($name) = $query->fetchrow()) {
        push @names, $name;
    }
    $query->finish();
    \@names;
}

sub entries_count_for_name {
    my $db = shift;

    my $command = <<EOF;
        SELECT name, COUNT(last_entry) AS entries
        FROM passwords LEFT JOIN audit USING (id)
        GROUP BY name
EOF

    my $query = my_database::run_query($db, $command);
    my ($name, $ents);
    my @names;

    while (($name, $ents) = $query->fetchrow()) {
        my @row = ($name, $ents);
        push @names, \@row;
    }
    $query->finish();
    \@names;
}

sub entries_count_for_name_w_total {
    my $db = shift;

    my $command = <<EOF;
        SELECT
            IF(name IS NULL, "Total Entries", name) AS name,
            COUNT(last_entry) AS entries
        FROM passwords LEFT JOIN audit USING (id)
        GROUP BY name
        WITH ROLLUP
EOF

    my $query = my_database::run_query($db, $command);
    my ($name, $ents);
    my @names;

    while (($name, $ents) = $query->fetchrow()) {
        my @row = ($name, $ents);
        push @names, \@row;
    }
    $query->finish();
    \@names;
}

sub oldest_entry_for_name {
    my $db = shift;

    my $command = <<EOF;
        SELECT name, MIN(last_entry) AS oldest_entry
        FROM passwords AS pw LEFT JOIN audit USING(id)
        GROUP BY name
EOF

    my $query = my_database::run_query($db, $command);
    my ($name, $acc);
    my @names;

    while (($name, $acc) = $query->fetchrow()) {
        my @row = ($name, $acc);
        push @names, \@row;
    }
    $query->finish();
    \@names;
}

sub id_name_access_audited_tbl {
    my $db = shift;

    my $command = <<EOF;
        SELECT
            t.id,
            t.name,
            t.access,
            (CASE
                WHEN (t.last_entry IS NOT NULL) THEN "yes"
                ELSE "no" END)
            AS audited
        FROM (
            SELECT *
            FROM
                passwords INNER JOIN priviledges USING(id) LEFT JOIN audit USING(id)
        ) AS t
        GROUP BY name
        ORDER BY id
EOF

    my $query = my_database::run_query($db, $command);
    my ($id, $name, $acc, $aud);
    my @names;

    while (($id, $name, $acc, $aud) = $query->fetchrow()) {
        my @row = ($id, $name, $acc, $aud);
        push @names, \@row;
    }
    $query->finish();
    \@names;
}

sub names_audited_exists {
    my $db = shift;

    my $command = <<EOF;
        SELECT name
        FROM passwords
        WHERE EXISTS (
            SELECT 1
            FROM audit
            WHERE passwords.id = audit.id
        )
EOF

    my $query = my_database::run_query($db, $command);
    my ($name);
    my @names;

    while (($name) = $query->fetchrow()) {
        push @names, $name;
    }
    $query->finish();
    \@names;
}

sub id_name_audit_w_union {
    my $db = shift;

    my $command = <<EOF;
        SELECT id, name, "yes" AS audited
        FROM audit INNER JOIN passwords USING(id)
        UNION
        SELECT id, name, "no" AS audited
        FROM passwords
        WHERE NOT EXISTS (
            SELECT 1
            FROM audit
            WHERE passwords.id = audit.id
        )
        ORDER BY name
EOF

    my $query = my_database::run_query($db, $command);
    my ($id, $name, $aud);
    my @names;

    while (($id, $name, $aud) = $query->fetchrow()) {
        my @row = ($id, $name, $aud);
        push @names, \@row;
    }
    $query->finish();
    \@names;
}
### ================================================================================================================ ###
my $database_obj = my_database->new(my_database->connect("users", "localhost", "3306"), "passwords");
my $database = $database_obj->{database}; #ugly hack!


my $table = get_passwords($database);my $names3 = names_with_priviledges($database);
#print Dumper($names3);
#print Dumper($table);

my $names = get_passwords_ordered($database);
#print Dumper($names);

my $names2 = distinct_like_where($database);
#print Dumper($names2);

my $names0 = names_with_priviledges($database);
#print Dumper($names0);

my $table2 = priviledges_for_name($database);
#print Dumper($table2);

my $table3 = priviledges_and_last_entry_for_name($database);
#print Dumper($table3);

my $names4 = names_non_audited($database);
#print Dumper($names4);

my $table4 = entries_count_for_name($database);
#print Dumper($table4);

my $table5 = entries_count_for_name_w_total($database);
#print Dumper($table5);

my $table6 = oldest_entry_for_name($database);
#print Dumper($table6);

my $table7 = id_name_access_audited_tbl($database);
#print Dumper($table7);

my $names5 = names_audited_exists($database);
#print Dumper($names5);

my $table8 = id_name_audit_w_union($database);
#print Dumper($table8);