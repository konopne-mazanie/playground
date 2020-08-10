var header = `
<h1>Priklad 2/3/4</h1>
`;

var navbar = `
<a href="index.html" class="main_page">Hlavna stranka</a>
<a href="galery.html" class="galery">Galeria</a>
<a href="blog.html" class="blog">Blog</a>
<a href="contacts.html" class="contacts">Kontakty</a>
<a href="subpage.html" class="subpage">O nas</a>
<a href="login.html" class="login" style="float: right;">Prihlasenie</a>
<a href="registracia.html" class="register" style="float: right;">Registracia</a>
`;

var footer = `
<h2>&copy; 2020 janeviemus.xx</h2>
`;

window.onload = function(ev) {
    document.querySelector(".header").innerHTML = header;
    document.querySelector(".navbar").innerHTML = navbar;
    document.querySelector(".footer").innerHTML = footer;
};
