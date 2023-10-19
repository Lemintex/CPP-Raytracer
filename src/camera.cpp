#include "camera.h"

camera::camera(vec3d lookfrom, vec3d lookat, vec3d vup, float vfov, float aspect_ratio, float aperture, float focus_dist) {
    lens_radius = aperture / 2;
    float theta = vfov * M_PI / 180;
    float half_height = tan(theta / 2);
    float half_width = (16.0 / 9.0) * half_height;
    origin = lookfrom;
    w = vec3d::unit_vector(lookfrom - lookat);
    u = vec3d::unit_vector(vec3d::cross(vup, w));
    v = vec3d::cross(w, u);
    lower_left_corner = origin - u * half_width * focus_dist -v * half_height * focus_dist - w * focus_dist;
    horizontal = u * 2 * half_width * focus_dist;
    vertical = v * 2 * half_height * focus_dist;
    samples_per_pixel = 10;
}

void camera::render(const surface_list &world)
{
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    for (int j = image_height - 1; j >= 0; --j)
    {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i)
        {
            vec3d color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; s++)
            {
                float u = (i + drand48()) / (image_width - 1);
                float v = (j + drand48()) / (image_height - 1);
                ray r = get_ray(u, v);
                color += get_color(r, world, bounce_limit);
            }
            vec3d::write_color(std::cout, color, samples_per_pixel);
        }
    }
    std::cerr << "\nDone.\n";
}

vec3d camera::get_color(const ray &r, const surface &world, int depth = 0)
{
    if (depth <= 0)
    {
        return vec3d(0, 0, 0);
    }
    hit_record rec;
    if (world.hit(r, 0.00001, MAXFLOAT, rec))
    {
        ray scattered;
        vec3d attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        {
            return attenuation * get_color(scattered, world, depth - 1);
        }
        else
        {
            return vec3d(0, 0, 0);
        }
        vec3d target = rec.p + rec.normal + vec3d::random_in_unit_sphere();
        return get_color(ray(rec.p, target - rec.p), world) * 0.5;
    }
    vec3d unit_direction = vec3d::unit_vector(r.direction());
    float t = 0.5 * (unit_direction.y() + 1.0);
    return vec3d(1.0, 1.0, 1.0) * (1.0 - t) + vec3d(0.5, 0.7, 1.0) * t;
}