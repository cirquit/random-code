module Main where

import           Graphics.Svg                        ( loadSvgFile )
import           Graphics.Rasterific.Svg             ( loadCreateFontCache, renderSvgDocument )
import           Codec.Picture
import           Codec.Picture.Types
import           Data.Vector.Storable.Mutable      -- ( IOVector(..) )

import           Data.Word                           ( Word8 )
import           Data.Function                       ( fix )

import           Data.Vector.Storable                ( Vector(..) )
import qualified Data.Vector.Storable          as V
import qualified Data.Vector.Generic.Mutable   as GM
import           Control.Monad                 as CM


import           SDL.Video.Renderer                   ( createRGBSurfaceFrom, PixelFormat(..), Surface() )
import           SDL.Vect                             ( V2(..) )
import           Foreign.C.Types                      ( CInt )

-- SDL dependency: sudo apt-get install libsdl2-dev
main :: IO ()
main = do
    let filepath = "img/homer-simpson.svg"
    mimage <- loadSVGImage filepath
    case mimage of
        Nothing      -> putStrLn "Image convertion failed."
        (Just image) -> do
            let surfaceSize :: V2 CInt
                surfaceSize = V2 1280 720
            surface <- createSurfaceFromSVG image surfaceSize
            -- show the surface
            putStrLn "Hopefully showing the image."


createSurfaceFromSVG :: Image PixelRGBA8 -> V2 CInt -> IO Surface
createSurfaceFromSVG image surfaceSize = do
    let rawImageData :: Vector Word8
        rawImageData = imageData image

        imWidth :: Int
        imWidth = imageWidth image

        pitch :: CInt
        pitch = fromIntegral imWidth

    mutableVector <- convertToMutableVector rawImageData
    createRGBSurfaceFrom mutableVector surfaceSize pitch RGBA8888

-- | as per https://github.com/haskell/vector/issues/175, there are some missing convertion functions
--   so we have to create one by hand
convertToMutableVector :: Vector Word8 -> IO (IOVector Word8)
convertToMutableVector v = do
    let len = V.length v
    mv <- GM.new len 
    CM.forM_ [0..(len - 1)] $ \i -> 
        GM.write mv i (v V.! i)
    return mv

loadSVGImage :: FilePath -> IO (Maybe (Image PixelRGBA8))
loadSVGImage filepath = do
    mdoc <- loadSvgFile filepath
    case mdoc of
      Nothing -> return Nothing
      Just doc -> do
        cache <- loadCreateFontCache "fonty-texture-cache"
        (finalImage, _) <- renderSvgDocument cache Nothing 96 doc
        return $ Just finalImage
