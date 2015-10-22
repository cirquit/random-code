module Main where

import Graphics.UI.Gtk
import Graphics.UI.Gtk.Builder

main :: IO ()
main = do
   initGUI
   builder <- builderNew
   builderAddFromFile builder "frame.glade"
   window <- builderGetObject builder castToWindow "window1"   
   widgetShowAll window
   onDestroy window mainQuit
   mainGUI