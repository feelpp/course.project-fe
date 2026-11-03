# Shared output directory for the brief and report. No shell escape required.
$pdf_mode = 1;
$out_dir = 'output/pdf';
$pdflatex = 'pdflatex -interaction=nonstopmode -halt-on-error -file-line-error %O %S';
