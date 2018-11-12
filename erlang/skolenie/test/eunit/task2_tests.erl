-module(task2_tests).
-include_lib("eunit/include/eunit.hrl").

-define(PRINT, true).
%%=========================================================
database() ->
	[
		{"abcd", 700},
		{"efgh", 41}
	].
%%---------------------------------------------------------
database_to_fn() ->
	fun(Command) -> task2:find_price(database(), Command) end.
%%=========================================================
emptyBarcode_test() ->
	?assertThrow(empty_barcode, task2:get_product(database_to_fn(), "")).
%%---------------------------------------------------------
unknownBarcode_test() ->
	?assertThrow(not_found, task2:get_product(database_to_fn(), "454felfjn")).
%%---------------------------------------------------------
knownBarcode_test() ->
	?assertMatch({"abcd", _}, task2:get_product(database_to_fn(), "abcd")).
%%=========================================================
displayPriceKnownItem_test() ->
	?assertEqual("700", task2:display_price(task2:get_product(database_to_fn(), "abcd"))).
%%---------------------------------------------------------
displayPriceUnknownItem_test() ->
	?assertThrow(not_found, task2:display_price(task2:get_product(database_to_fn(), "abcdef"))).
%%---------------------------------------------------------
formatPrice_test() ->
	?assertEqual("10", task2_private:format_price(10)).
%%---------------------------------------------------------
displayPriceMultiple_test() ->
	?assertEqual("741", task2:display_price_multiple(task2:get_products(database_to_fn(), "abcd, efgh"))).
%%---------------------------------------------------------
getProducts_test() ->
	?assertEqual([task2:get_product(database_to_fn(), "abcd"),
		task2:get_product(database_to_fn(), "efgh")],
		task2:get_products(database_to_fn(), "abcd, efgh")).
%%---------------------------------------------------------
parseBarcodes_test() ->
	?assertEqual(["abcd", "efgh"], task2_private:parse_commalist("abcd, efgh")).
%%---------------------------------------------------------
parseBarcodesSingle_test() ->
	?assertEqual(["abcd"], task2_private:parse_commalist(" abcd ")).
%%---------------------------------------------------------
csvParseline_test() ->
	?assertEqual({"barcode", 10}, task2_private:parse_line("barcode, 10")).
%%---------------------------------------------------------
csvParselineEmptyBarcode_test() ->
	?assertError(_, task2_private:parse_line(", 10")),
	?assertError(_, task2_private:parse_line(" , 10")).
%%---------------------------------------------------------
csvParselineInvalidPrice_test() ->
	?assertError(_, task2_private:parse_line("barcode, invalid_value")).
%%---------------------------------------------------------
csvParsefile_test() ->
	Result			=	task2:parse_file("test_file.csv"),
	Expect 			= 	database(),
	Reverse_Expect	= 	lists:reverse(database()),
	IsOk 			= 	if
							Expect 			== Result 	-> true;
							Reverse_Expect 	== Result 	-> true;
							true						-> false
	end,
	?assert(IsOk).
%%---------------------------------------------------------
handleCommand_test() ->
	?assertEqual("700", task2:handle_command(fun(Product) -> task2:display_price(Product) end,
		fun(Command) -> task2:find_price(task2:parse_file("test_file.csv"), Command) end, "abcd")).
%%---------------------------------------------------------
handleCommandMulti_test() ->
	FindPriceSingleFun 	= fun(Command) -> task2:find_price(task2:parse_file("test_file.csv"), Command) end,
	FindPriceMultiFun 	= fun(Commands) ->	task2:get_products(FindPriceSingleFun, Commands) end,
	?assertEqual("741", task2:handle_command(fun(Products) -> task2:display_price_multiple(Products) end,
		FindPriceMultiFun, "abcd, efgh")).