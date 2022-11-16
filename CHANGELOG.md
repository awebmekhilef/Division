# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [3.0.0] - 2022-11-09
### Added
- 3D model loading using assimp
- Multiple light support in shader
- Window buffer MSAA
- ImGui debug panels (stats and entities)
- Parent + child transformation hierarchy
- Update viewport on window resize
- Rendering debug light meshes
- Arcball camera for viewing in all directions
- Skybox (no more ugly flat background)

### Changed
- Fix IBO not configured correctly in mesh
- Calculate normal by taking into account model matrix in shader
- Shader now takes in view and projection matrices seperately

### Removed
- Old backpack textures (replaced with properly oriented ones)

## [2.0.0] - 2022-11-06
### Added
- Material system with diffuse and specular textures
- Single point light shading
- Basic orbital camera
- Mesh class (with quad and cube preconfigured)
- Integer upload to shader

### Changed
- Loading shader from file

### Removed
- Graphics API abstraction (supports only OpenGL for now)

## [1.0.0] - 2022-10-22
### Added
- Cross platform windowing and context via GLFW
- OpenGL abstraction classes (vertex arrays, buffers, shaders, etc.)
- Basic renderer
