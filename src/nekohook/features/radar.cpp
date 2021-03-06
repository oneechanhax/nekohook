
/*
 * Nekohook: Free, fast and modular cheat software
 * Copyright (C) 2018 Rebekah Rowe
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

// Disabled because of gui dependancy

/*#include "../gui/base/CBaseWindow.hpp"
#include "../util/catvars.hpp"
using namespace gui::base;  // LET US IN >_>
#include "../framework/drawing.hpp"
#include "../framework/game.hpp"

#include "radar.hpp"

// TODO, fix colors?

namespace features::radar {

static CatEnum radar_menu({"Visuals", "Radar"});
static CatVarBool enabled(radar_menu, "radar", false, "Enable Radar");
static CatVarInt radar_size(radar_menu, "radar_size", 200, "Radar Size");
static CatVarInt radar_zoom(radar_menu, "radar_zoom", 1, "Radar Zoom", "uhh",
                            -100, 100);
static CatEnum radar_type_enum({"Square", "Circle"});
static CatVarEnum radar_type(radar_menu, radar_type_enum, "radar_type", 0,
                             "Radar Type");


void CRadar::Draw() {
    if (!enabled) return;  // Shitty visual fixing

    // Draw the base
    if (!radar_type)          // square
        CBaseWindow::Draw();  // We can use window for this
    else {                    // Circle
        auto size_fix = (size.first + size.second) /
                        2;  // We need to average sizes as we draw weird circles
        draw::CircleFilled(global_pos.first + size_fix / 2,
                           global_pos.first + size_fix / 2, size_fix, 20,
                           colors::gray.Transparent());
        draw::Circle(global_pos.first + size_fix / 2,
                     global_pos.first + size_fix / 2, size_fix, 20,
                     colors::white);
    }

    // Draw lines on it, looks cool like lmaobox
    // Up down
    draw::Line(global_pos.first + size.first / 2,
               global_pos.second + size.second / 4, 0, size.second / 2,
               colors::white);
    // left right
    draw::Line(global_pos.first + size.first / 4,
               global_pos.second + size.second / 2, size.first / 2, 0,
               colors::white);

    // We want to be ingame to draw entitys
    if (!game::GetInGame()) return;

    // We need a local player to get the y angle as well as the origin
    auto local_ent = GetLocalPlayer();
    if (!local_ent || GetDormant((CatEntity*)local_ent)) return;
    auto loc_origin = GetOrigin((CatEntity*)local_ent);
    // auto camera_yaw = GetCameraAngle(local_ent).y;

    // Here we draw entitys
    auto ent_count = GetEntityCount();
    for (int i = 0; i < ent_count; i++) {
        auto entity = GetEntity(i);
        if (!entity || GetDormant(entity)) continue;
        if (GetType(entity) != ETYPE_PLAYER || !GetAlive(entity)) continue;
        if (entity == (CatEntity*)local_ent) continue;

        // Get the entitys position relative to us
        CatVector radar_pos = GetOrigin(entity) - loc_origin;

        // Here we can affect the delta with the zoom param
        if (radar_zoom) radar_pos /= (float)radar_zoom * 0.25;

        // Here we should transform the position of the entity based on our
        // yaw... but i dont know math so uhh, too bad

        // Clamp it to the radar bounds, we clamp differently depending on shape
        if (!radar_type) {                  // square
            if (radar_pos.x < -size.first)  // left
                radar_pos.x = -size.first;
            if (radar_pos.y < -size.second)  // top
                radar_pos.y = -size.second;
            if (radar_pos.x > size.first)  // right
                radar_pos.x = size.first;
            if (radar_pos.y > size.second)  // bottom
                radar_pos.y = size.second;
        } else {  // circle
            // Angle math is hard >_> someone tutor me ;(
            // First we check if we need to clamp in the first place
            auto size_fix = (size.first + size.second) / 2;
            if (radar_pos.DistTo(CatVector()) > size_fix) {
                // Instead of clamping out in, we will do the reverse
                // We get the delta and multiply it by size to get it clamped
                // TODO, this code needs testing
                auto delta_x = radar_pos.x / radar_pos.y;
                auto delta_y = radar_pos.y / radar_pos.x;
                radar_pos.x = delta_x * size_fix;
                radar_pos.y = delta_y * size_fix;
            }
        }

        // Draw the entity on the radar
        // TODO, radar still broke, so ill do this later
        // draw::RectFilled()
    }
}

void Init() {}

}  // namespace features::radar
//*/
