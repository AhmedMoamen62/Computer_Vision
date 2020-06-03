img = imread ('figs/dog-emboss.png');
figure,imshow (img)
img1 = imread ('data/dog.jpg');
figure,imshow (img1)
function btn_down (obj, evt)
  cp = get (gca, 'CurrentPoint');
  x = round (cp(1, 1));
  y = round (cp(1, 2));
  img = get (findobj (gca, "type", "image"), "cdata");
  img_v = NA;
  if (x > 0 && y > 0 && x <= columns (img) && y <= rows (img))
    img_v = squeeze (img(y, x, :));
  endif

  if (numel (img_v) == 3) # rgb image
    title(gca, sprintf ("(%i, %i) = r(%i), g(%i), b(%i)", x, y, img_v(1), img_v(2), img_v(3)));
  elseif (numel (img_v) == 1) # gray image
    title(gca, sprintf ("(%i, %i) = %i", x, y, img_v));
  endif
endfunction

set (gcf, 'WindowButtonDownFcn', @btn_down);