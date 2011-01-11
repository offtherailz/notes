% Notes on CSS
% Peter Aronoff
% 2010-01-03 (with follow-up on 2011-01-09)

## How to link to style sheets

External style sheets are good; use them. (An exception exists for mega, mega sites, but for all normal purposes, this is a flat rule.) There are two basic ways: you can use HTML or CSS.

+ First, there's the HTML way (in HTML5 the `type` attribute is no longer required):

		<link rel="stylesheet" type="text/css" href="/css/global.css">



+ And here is the CSS way:

		<style type="text/css">
			@import url("/css/global.css");
		</style>

## Selector types

When you want to apply style, it's generally to numerous similar items. For example, you might want all `<h1>` elements to look a certain way. Of you might want to style the first paragraph of every blog entry differently from the remaining paragraphs.

To pick out what you want to style, you use selectors. The selectors themselves come in various types.

+	Type selectors (also known as tag or element selectors) pick out every example of a specific HTML element. For example, to style every `<h1>` element, you could simply do this:

		h1 { font-size: 14em; }

	Note that no special punctuation precedes the `h1` that introduces the selector.

+	Class selectors pick out members of a given HTML class (defined in a `<div>` or `<span>` or in a specific element like an individual list: `<ul class="debts">`). Class selectors differ from type selectors visually: they require a `.` (a period) before the class name. The following selector would make all the text in a debt class appropriately red.

		.debt { color: red; }

	There are a few rules concerning class selectors:

	+ The selector must start with a period.
	+ The only valid characters are letters, numbers, a hyphen or an underscore.
	+ The first character after the period must be a letter.
	+ Class names are case sensitive.

+	ID selectors target specific, unique elements on a page. Like a class selector, an ID selector picks out an item that is first specified in the HTML. Also, like a class selector, there's a bit of syntax at the start of the ID selector's name that lets the browser know it's an ID selector rather than a type or class selector.

	To use an ID selector, you type the name of the ID preceded by a `#`. In this respect, an ID selector is exactly parallel to a class selector. And in fact, all the same rules apply to the valid names that can folow the `#`. So if you had an ID for 'debt' instead of a class, you would simply do this:

		#debt { color: red; }

+	Group selectors allow you to target more than one selector at a time. The selectors can be of the same kind or different. To use a group selector, simply provide a commma-separated list of selectors to target, thus:

		h1, .debt, #warning {
			color: red;
			background: white;
		}

	Note that this method is especially good for initial resets.

+	Descendent selectors open up a larger world of specificity. Instead of aiming at all `<h1>` elements or all `.debt` items, you can specify that you only want to style the `<h1>` items within a certain part of the page. You do this by walking the page's tree and finding an appropriate descendent chain. For example, let's imagine that we have a `<div>` with an ID of `debt`, and that you want to style the paragraphs of that div in a specific way. Easy:

		#debt p {
			color: red;
			background:white;
		}

+	Pseudo-class and pseudo-element selectors allow you to aim at parts of the page that don't have specific (or distinct) HTML elements, but are important and useful for styling. Probably the most important pseudo-classes are for links:

		+ `a:link`
		+ `a:visited`
		+ `a:hover`
		+ `a:active`

	These four allow you to customize the way that links in any state look on your page. (You can also use these in descendent selectors to vary how links on one part of the page look.)

	A few other useful pseudo-items to wrap things up. In addition to links, you can do fancy print-like styling with the `:first-letter` or `:first-line` pseudo-elements. Other good pseudo-elements to remember are `:before`, `:after`, `:focus` and `:first-child`. The `:focus` selector is especially useful for forms, and the other three let you do complex things to particular parts of the page. (Note that you can get generated content from `:before` and `:after`.)

+	Child selector, as the name suggests, lets you specify your target as the child of a specific element. This can be useful because the normal descendent selector will find things at any depth. That is, `h1 p` finds a paragraph anywhere below a first-level heading. But `h1 > p` specifies only a paragraph directly below the right heading.

+	Adjacent sibling selectors are both very specific and oddly general. I understand how they work, but I'm not sure how often I would want one or be able to count on it not blowing up on me. Here's the deal: when you look at the parse tree of a page, you can use an adjacent sibling selector to pick out anything immediately to the left of an item. The syntax is a `+` between the two items. So `h2 + p` would select any paragraphs that came right after an `<h2>`. Note that there might be _many such items_. One to think about some more.

+	Attribute selectors: I like these since they feel nearly programmatic. Using an attribute selector, you can pick an element that has a specific attribute - for example `a[title]` gets only the links that have a title attribute. But even better, you can specify links with an attribute _with a specific value_: `a[href="http://www.google.com"]`. Finally, you can use standard anchors (`^` or `$`) or a wildcard (`*`) to find text values in specific places:

		+ `a[href^="http"]`  // Only external links
		+ `a[href$="pdf"]`   // Only links to pdfs
		+ `a[href*="apple"]` // Any link with 'apple' anywhere in it
