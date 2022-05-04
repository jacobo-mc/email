#!/depot/path/tclsh

# This is a CGI script that demonstrates error processing.

package require cgi

cgi_eval {
    source example.tcl

    cgi_input

    cgi_title "This CGI script contains an intentional error."

    cgi_body {
	p "The page that you are now reading is being generated by a
	CGI script that contains an intentional error."

	cgi_debug -on

	p "Debugging is enabled, so the error message will be shown in
the browser window (below).  Disable this by commenting out the
cgi_debug command and reloading this script."

	cgi_number_list {
	    cgi_li "List item 1"
	    cgi_li "List item 2"
	    cgi_lix "List item 3 - intentionally misspelled"
	    cgi_li "List item 4"
	}
    }
}
