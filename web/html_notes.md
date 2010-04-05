% Notes on HTML
% Peter Aronoff
% 2009-12-29

# Notes on HTML

## Lists

When nesting lists, note the following. The `<ol>` and `<ul>` elements are block level, and they can only have `<li>` elements directly inside them. In order to have nested lists, therefore, you must put a new `<ul>` or `<ol>` elements inside an *unclosed* `<li>` element, thus:

		<ul>
			<li>Scripting languages
				<ul>
					<li>Perl</li>
					<li>Ruby</li>
					<li>Python</li>
				</ul>
			</li> <!-- Scripting languages item closes here -->
			<li>Systems languages
				<ul>
					<li>C</li>
					<li>Go</li>
				</ul>
			</li> <!-- Systems languages closes here -->
		</ul> <!-- Outer list closes here>
