-module(task2).
-include("task2_types.hrl").
-compile(export_all).
-import(task2_private, [format_price/1, parse_commalist/1, for_each_line/1]).

%%=========================================================
-spec get_product(atom(), string()) -> product().
get_product(FindPrice, Barcode) ->
	case Barcode of
		""		->	throw(empty_barcode);
		_		->	FindPrice(Barcode)
	end.
%%=========================================================
-spec find_price(list(product()), string()) -> product().
find_price(Database, Barcode) ->
	case lists:filter(fun(Elem) -> {Elem_Barcode, _} = Elem, Elem_Barcode =:= Barcode end, Database) of
		[]		->	throw(not_found);
		List 	->	hd(List)
	end.
%%=========================================================
-spec get_product_from_barcode(list(product())) -> product().
get_product_from_barcode(Database) ->
	get_product(get_barcode(), Database).
%%=========================================================
-spec display_price(product()) -> string().
display_price(Product) ->
	{_, Price} = Product,
	format_price(Price).
%%=========================================================
-spec get_products(atom(), string()) -> list(product()).
get_products(FindPrice, Input) ->
	[get_product(FindPrice, Barcode) || Barcode <- parse_commalist(Input)].
%%=========================================================
-spec display_price_multiple(list(product())) -> string().
display_price_multiple(Products) ->
	{_, Price} = hd(Products),
	display_price_multiple(Price, tl(Products)).
%%---------------------------------------------------------
display_price_multiple(Current_Price, []) ->
	format_price(Current_Price);
%%---------------------------------------------------------
display_price_multiple(Current_Price, Products) ->
	{_, Price} = hd(Products),
	display_price_multiple(Price + Current_Price, tl(Products)).
%%=========================================================
-spec parse_file(string()) -> list(product()).
parse_file(FileName) ->
	{ok, Device} = file:open(FileName, [read]),
	try for_each_line(Device)
		after file:close(Device)
    end.
%%=========================================================
-spec get_barcode() -> string().
get_barcode() ->
	Barcode = io:get_line("Enter barcode: "),
	string:chomp(Barcode).
%%=========================================================
-spec handle_command(atom(), atom(), string()) -> string().
handle_command(DisplayPrice, FindPrice, Command) ->
	DisplayPrice(FindPrice(Command)).
%%=========================================================
main_single() ->
	io:format("~p~n", [handle_command(display_price, fun(Command) -> find_price([], Command) end, get_barcode())]).
%%=========================================================
main_multi() ->
	FindPriceSingleFun 	= fun(Command) 	->	find_price([], Command) end,
	FindPriceMultiFun 	= fun(Commands) ->	get_products(FindPriceSingleFun, Commands) end,
	io:format("~p~n", [handle_command(display_price_multiple, FindPriceMultiFun, get_barcode())]).