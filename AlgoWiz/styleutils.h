/**
 * @file StyleUtils.h
 * @brief Header file for style utilities, including shared button styles for consistent UI design across the application (e.g., game mode buttons).
 * @author Jared Pratt, Grant Beck
 * @date 2025-04-25
 */

#ifndef STYLEUTILS_H
#define STYLEUTILS_H

#include <QString>

/**
 * @brief Returns the shared style sheet string for game buttons.
 *
 * This style provides an orange theme with hover and pressed effects for QPushButton widgets,
 * ensuring consistent styling across the game's interactive buttons.
 *
 * @return Reference to the static QString containing the style sheet.
 */
inline const QString &gameButtonStyle() {
    static const QString s = R"(
    QPushButton {
      background: rgba(255,165,0,0.15);
      border: 2px solid #FFA500;
      border-radius: 8px;
      color: #ffffff;
      font: 700 18px 'Trebuchet MS';
      padding: 8px 16px;
    }
    QPushButton:hover {
      background: #FFA500;
      color: #000000;
    }
    QPushButton:pressed {
      background: #FF7B00;
      color: #000000;
    }
  )";
    return s;
}

#endif // STYLEUTILS_H
