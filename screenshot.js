const puppeteer = require('puppeteer');
const fs = require('fs');
const path = require('path')

const screenshotFolder = 'screenshots/'
const markdownPath = 'site/docs'; 

var fileList = []; 

//Development purpose only 
//See output https://github.com/Evident-Industrial/NDE_Open_File_Format_Private/actions/workflows/artifact-puppeteer.yml to download artifact
function Screenshot() {
  if (!fs.existsSync(screenshotFolder)) {
    fs.mkdirSync(screenshotFolder);
  }

  (async () => {
      const browser = await puppeteer.launch({headless: 'new'});

    const page = await browser.newPage();

    FindMarkdownFiles([path.resolve(__dirname, markdownPath)]);

    const files = await fileList.map(file => 'docs/' + path.relative(markdownPath, file)); 

    for (var file of files) {
      if (path.basename(file, '.html') === 'overview') {
        await page.goto('http://localhost:4000/NDE_Open_File_Format/'); 
        await page.screenshot({ path: screenshotFolder + path.basename(file, '.html') + '.png' }); 
      } 
      else {
        await page.goto('http://localhost:4000/NDE_Open_File_Format/' + file); 

        const bodyHandle = await page.$('body');
        const { width, height } = await bodyHandle.boundingBox();
        await bodyHandle.dispose();

        console.log("file: " +  file + " height: " + height); 

        await page.setViewport({
          width: Math.ceil(1200),
          height: Math.ceil(height),
        });
      
        await page.screenshot({ path: screenshotFolder + path.basename(file, '.html') + '.png', fullPage: true }); 
      }
    }
    
    await browser.close();
  })();
}

function FindMarkdownFiles(folderPaths) {
  if (folderPaths.length === 0) {
    return
  }

  folderPaths.forEach(folderPath => {
    const results = fs.readdirSync(folderPath)
    const mdFiles = results.filter(file => path.extname(file).toLowerCase() === '.md')
    const files = mdFiles.map(file => path.parse(file).name)
    const folders = results.filter(res => fs.lstatSync(path.resolve(folderPath, res)).isDirectory())
    const innerFolderPaths = folders.map(folder => path.resolve(folderPath, folder))
    
    files.forEach(file => {
      fileList.push(folderPath + '/' + file + '.html')
    });

    FindMarkdownFiles(innerFolderPaths)
  })
}

Screenshot()