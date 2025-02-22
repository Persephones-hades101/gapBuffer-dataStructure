import pygame
import subprocess

# Initialize Pygame
pygame.init()
screen = pygame.display.set_mode((800, 600))
pygame.display.set_caption("Pygame Text Editor")

# Set up fonts and colors
font = pygame.font.Font(None, 36)
white = (255, 255, 255)
black = (0, 0, 0)

# Start C++ subprocess (Runs gap_buffer.cpp)
cpp_process = subprocess.Popen(
    ["./gap_buffer"], stdin=subprocess.PIPE, stdout=subprocess.PIPE, text=True
)

# Function to send input to C++ and get updated text


def send_input_to_cpp(char):
    cpp_process.stdin.write(char)
    cpp_process.stdin.flush()
    return cpp_process.stdout.readline().strip()


running = True
text = ""

while running:
    screen.fill(black)  # Clear screen

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_BACKSPACE:
                text = send_input_to_cpp("\b")  # Send backspace to C++
            elif event.key == pygame.K_LEFT:
                text = send_input_to_cpp("<")  # Move cursor left
            elif event.key == pygame.K_RIGHT:
                text = send_input_to_cpp(">")  # Move cursor right
            elif event.key == pygame.K_RETURN:
                text += "\n"
            else:
                # Send character to C++
                text = send_input_to_cpp(event.unicode)

    # Render text
    rendered_text = font.render(text, True, white)
    screen.blit(rendered_text, (20, 50))

    pygame.display.flip()  # Update display

# Close C++ process when quitting
cpp_process.stdin.close()
cpp_process.stdout.close()
cpp_process.wait()
pygame.quit()
