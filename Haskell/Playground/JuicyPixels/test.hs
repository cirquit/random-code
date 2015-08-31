import Codec.Picture
import Codec.Picture.Types
import System.Directory (getCurrentDirectory)
import Codec.Picture.Gif

main = do
  dir <- getCurrentDirectory
  case createGif (dir ++ "/guh.gif") of
    (Left err) -> putStrLn $ "Error occured: " ++ err
    (Right io) -> io


createImg :: FilePath -> IO ()
createImg fp = writeBitmap fp  $ generateImage pixelRenderer 255 255
  where pixelRenderer x y = PixelRGB8 255 (fromInt x) (fromInt y)

--fromInt :: Int -> Word8
fromInt = fromIntegral


redPalette :: Palette
redPalette = generateImage toPal 256 1
  where toPal x _ = PixelRGB8 (i x) 0 0
        i         = fromIntegral

createGif :: FilePath -> Either String (IO ())
createGif fp = writeGifImages fp LoopingForever list
  where --gif1 = generateImage (\x y -> fromIntegral 0)   255 255
        --gif2 = generateImage (\x y -> fromIntegral 100) 255 255
        --gif3 = generateImage (\x y -> fromIntegral 200) 255 255
        list = map (\x -> (redPalette, 1, (generateImage (\_ _ -> fromIntegral x) 255 255))) [0..255]
  -- where gifs = map (\x -> generateImage x 255 255) 
  --       pixelRenderer x y = PictureRGB8