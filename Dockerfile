# Use the Nginx image from Docker Hub
FROM nginx:alpine

# Copy the content of your application to the container's web root directory
COPY . /usr/share/nginx/html

# Replace the default nginx.conf with your custom file
COPY nginx.conf /etc/nginx/nginx.conf

# Expose port 80 to the host machine
EXPOSE 80
