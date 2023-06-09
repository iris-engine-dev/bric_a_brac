#pragma once

#include <functional>
#include <string>
#include <vector>

#include "colour.h"
#include "degree.h"
#include "manual_object.h"
#include "quaternion.h"
#include "render_entity.h"
#include "vector3.h"

#include "Ogre.h"
#include "OgreApplicationContext.h"

namespace bab
{

/**
 * Class to handle all things related to rendering (and by extension windowing).
 */
class GraphicsManager : private ::OgreBites::ApplicationContext, ::OgreBites::InputListener
{
  public:
    /**
     * Construct a new GraphicsManager.
     */
    GraphicsManager();

    /**
     * GraphicsManager specific cleanup.
     */
    ~GraphicsManager() override;

    /**
     * Add a mesh to the scene.
     *
     * @param mesh_name
     *   Name of mesh to load, must exist in a resource location.
     *
     * @param position
     *   The world position of the mesh.
     *
     * @param orientation
     *   The world orientation of the mesh.
     *
     * @param casts_shadows
     *   Whether the model can cast a shadow.
     */
    void add_mesh(
        const std::string &mesh_name,
        const Vector3 &position,
        const Quaternion &orientation,
        bool casts_shadows);

    /**
     * Add a plane (XZ) to the scene.
     *
     * @param width
     *   The width of the mesh (x axis).
     *
     * @param height
     *   The height of the mesh (z axis).
     *
     * @param x_segments
     *   How many segments make up the plane in the x direction.
     *
     * @param z_segments
     *   How many segments make up the plane in the z direction.
     *
     * @param casts_shadows
     *   Whether the model can cast a shadow.
     *
     * @param material_name
     *   The name of the material to add to the plane.
     */
    void add_plane(
        float width,
        float height,
        std::uint32_t x_segments,
        std::uint32_t z_segments,
        bool casts_shadows,
        const std::string &material_name);

    /**
     * Add a new named material to the engine which simply applies a texture.
     *
     * @param name
     *   The name for the new material.
     *
     * @param texture_name
     *   Name of texture to load, must exist in a resource location.
     */
    void add_material(const std::string &name, const std::string &texture_name);

    /**
     * Add a new cube to the scene.
     *
     * @param position
     *   World position of the cube.
     *
     * @param scale
     *   The scale of the cube (x, y and z direction).
     *
     * @param material_name
     *   The name of the material to add.
     *
     * @returns
     *   Pointer to newly added entity.
     */
    RenderEntity add_cube(const Vector3 &position, float scale, const std::string &material_name);

    /**
     * Add a new manual object to the scene.
     *
     * @returns
     *   The newly added manual object.
     */
    ManualObject add_manual_object();

    /**
     * Add a new spotlight to the scene.
     *
     * @param position
     *   The position in world space of the light.
     *
     * @param direction
     *   The direction the light is pointing.
     *
     * @param colour
     *   Colour of the light.
     *
     * @param inner_angle
     *   Angle of the inner cone of the light.
     *
     * @param outer_angle
     *   Angle of the outer cone of the light.
     */
    void add_spot_light(
        const Vector3 &position,
        const Vector3 &direction,
        const Colour &colour,
        const Degree &inner_angle,
        const Degree &outer_angle);

    /**
     * Add a new directional light to the scene.
     *
     * @param direction
     *   The direction the light is pointing.
     *
     * @param colour
     *   Colour of the light.
     */
    void add_directional_light(const Vector3 &direction, const Colour &colour);

    /**
     * Add a new point light to the scene.
     *
     * @param position
     *   The position in world space of the light.
     *
     * @param colour
     *   Colour of the light.
     */
    void add_point_light(const Vector3 &position, const Colour &colour);

    /**
     * Set the sky dome for the scene.
     *
     * @param material_name
     *   The name of the material to add to the dome.
     *
     * @param curvature
     *   The curvature of the dome.
     *
     * @param tiling
     *   How many times to tile the texture.
     */
    void set_sky_dome(const std::string &material_name, float curvature, float tiling);

    /**
     * Register a callback, which will get fired on frame start.
     *
     * @param callback
     *   The callback to register.
     */
    void register_frame_start_callback(std::function<void()> callback);

    /**
     * Register a callback, which will get fired on frame end.
     *
     * @param callback
     *   The callback to register.
     */
    void register_frame_end_callback(std::function<void()> callback);

    /**
     * Block and start the render loop.
     */
    void start_rendering();

  private:
    /**
     * Called by Ogre when the frame starts.
     *
     * @param evt
     *   Ogre frame event object.
     *
     * @returns
     *   True if rendering should continue, false if it should abort.
     */
    bool frameStarted(const ::Ogre::FrameEvent &evt) override;

    /**
     * Called by Ogre when the frame ends.
     *
     * @param evt
     *   Ogre frame event object.
     *
     * @returns
     *   True if rendering should continue, false if it should abort.
     */
    bool frameEnded(const ::Ogre::FrameEvent &evt) override;

    /**
     * Handle key pressed event.
     *
     * @param evt
     *   Ogre keyboard event object.
     *
     * @returns
     *   True if event should be consumed and not propagated further, otherwise false.
     */
    bool keyPressed(const ::OgreBites::KeyboardEvent &evt) override;

    /** Ogre scene manager object. */
    ::Ogre::SceneManager *scene_manager_;

    /** Collection of callbacks to fire on frame start. */
    std::vector<std::function<void()>> frame_start_callbacks_;

    /** Collection of callbacks to fire on frame end. */
    std::vector<std::function<void()>> frame_end_callbacks_;
};

}
