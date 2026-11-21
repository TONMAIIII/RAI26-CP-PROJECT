import fitz  # PyMuPDF

doc = fitz.open("Compro2026Report.pdf")

# Set border properties
margin = 15     # 10px distance from page edges
line_width = 2 # 2px line thickness

for page in doc:
    rect = page.rect
    
    # Calculate box coordinates inset by 10px on every side
    # Offsetting by half line width (2px) centers the 4px stroke along the 10px margin line
    offset = margin + (line_width / 2)
    border_rect = fitz.Rect(
        offset, 
        offset, 
        rect.width - offset, 
        rect.height - offset
    )
    
    # Draw 4px black rectangle
    page.draw_rect(border_rect, color=(0, 0, 0), width=line_width)

doc.save("Compro2026Report1.pdf")
doc.close()