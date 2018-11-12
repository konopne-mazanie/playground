use strict;
use warnings;
use v5.12;

use Test::Most tests => 1;

subtest cmp1 => sub {
    plan tests => 2;
 
    #describe design of the structure
    my %leaf_node = (
	    id      => re('^\d+$'),
	    name    => re('^\w+$'),
    );

    my %branch_node = %leaf_node; #add id & name to branch node
    $branch_node{children} = array_each(any (\%branch_node, \%leaf_node));  #add children array to branch node (via autovifi)
                                                                            #which can contain both branch nodes or leaf nodes
    my $tree = array_each(any(\%branch_node, \%leaf_node)); #create tree - array consisting of branches or leafs

    #tests
    cmp_deeply good_tree(), $tree;
    cmp_deeply bad_tree(), $tree; #this one should fail
};

sub good_tree() {
    [
        {
            id          =>  123,
            name        =>  "abc"
        },
        {
            id          =>  124,
            name        =>  "abd",
            children    =>  [
                            {
                                id          =>  125,
                                name        =>  "abe"
                            }
            ]
        }
    ];
}

sub bad_tree() {
    [
        {
            id          =>  123,
            name        =>  "abc"
        },
        {
            id          =>  124,
            name        =>  "abd",
            children    =>  [
                            {
                                id          =>  125,
                                naame        =>  "abe" #wrong param name
                            }
            ]
        }
    ];
}