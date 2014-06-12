var w = new Window();
w.width = 1280;
w.height = 800;
w.visible = true;

var t = new TextEdit();
t.appendTo(w);
t.visible = true;
t.left = 0;
t.top = 0;

var b = new Button();
b.text = "Button1"
b.appendTo(w);
b.visible = true;
b.addEventListener('click', function() {
try {
	(0, eval)(t.text);
} catch (e)
{
	w.alert(e.message);
}
})
b.height = 200;

w.addEventListener('resize', function() {
    t.width = this.width;
    t.height = this.height - 200;
    b.top = this.height - 200;
    b.width = this.width;
});