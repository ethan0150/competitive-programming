/*
 * RPGMap.java -- RPG map
 *  Project Sprita
 *
 *
 *
 */

package com.xdavidwu.sprita;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.io.FileInputStream;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Properties;

public class RPGMap extends JPanel {
	public final static int TYPE_WALKABLE=1;
	public final static int TYPE_BLOCK=2;
	public final static int TYPE_HORIZONTAL_WALKABLE=3;
	public final static int TYPE_VERTICAL_WALKABLE=4;
	public final static int TYPE_ENDPOINT=5;
	public final static int TYPE_CHECK=6;

	private RPGGame game;
	private int blockWidth=50;
	private int blockHeight=50;
	private int blockHorizontal=75;
	private int blockVertical=50;

	private Image[] blockImages = new Image[6];
	private int[][] map;
	private Image[][] mapLayer;
	private Image[][] itemLayer;
	private Image[][] wallLayer;
	private Image[][] npcLayer;
	private Chest[][] chests;
	private Boss[][] bosses;
	private NPC[][] npcs;
	private Image[] characterImage = new Image[12];
	private Character cha;
	private ArrayList<Character> characters=new ArrayList<>();
	private int encounterRate;

	private int currentX=0;
	private int currentY=0;
	private int posX=0;
	private int posY=(-1)*blockHeight;
	private int toX=0;
	private int toY=posY;
	private int aniSpeed=4;
	private int aniInterval=80;
	private int aniPhase=0;
	private int face=Character.FACE_EAST;

	private BattleFeild bf;

	private Sentence dialogSentence;
	private int sentenceSelected=0;
	private String dialogBackgroundPath;
	private Image dialogBackground;
	private JPanel dialogPanel=new JPanel();
	private JScrollPane dialogScrollPane=new JScrollPane(dialogPanel);
	private JTextArea dialogMainTextArea=new JTextArea();
	private ArrayList<JTextArea> dialogOptionTextAreas=new ArrayList<>();
	private Font dialogFont;
	private Dimension dialogMinSize;
	private Dimension dialogMaxSize;
	private Dimension dialogWithProtraitMinSize;
	private Dimension dialogWithProtraitMaxSize;
	private int dialogProtraitWidth=0;
    private String mapName;
	private Properties mapFile=new Properties();

	public interface OnEndPointListener{
		public void onEndPoint(RPGMap m,int x,int y);
	}

	public interface OnMoveListener{
		public void onMove(RPGMap m,int x,int y);
	}

	public interface OnCheckListener{
		public void onCheck(RPGMap m,int x,int y);
	}

	private OnEndPointListener mOnEndPoint;
	private OnMoveListener mOnMove;
	private OnCheckListener mOnCheck;

	private KeyAdapter keyAction = new KeyAdapter(){
		@Override
		public void keyPressed(KeyEvent e) {
			super.keyPressed(e);
			switch(e.getKeyCode()){
				case KeyEvent.VK_UP:
					if(dialogSentence!=null){
						if(sentenceSelected>0){
							dialogOptionTextAreas.get(sentenceSelected).setBackground(Utils.TRANSPARENT);
							sentenceSelected--;
							repaint();
						}
					}else{
						face=Character.FACE_NORTH;
						if(currentY!=0) moveCharacter(currentX,currentY-1);
						repaint();
					}
					break;
				case KeyEvent.VK_RIGHT:
					if(dialogSentence==null){
						face=Character.FACE_EAST;
						if(currentX!=blockHorizontal-1) moveCharacter(currentX+1,currentY);
						repaint();
					}
					break;
				case KeyEvent.VK_DOWN:
					if(dialogSentence!=null){
						if(sentenceSelected+1<dialogSentence.getChildCount()){
							dialogOptionTextAreas.get(sentenceSelected).setBackground(Utils.TRANSPARENT);
							sentenceSelected++;
							repaint();
						}
					}else{
						face=Character.FACE_SOUTH;
						if(currentY!=blockVertical-1) moveCharacter(currentX,currentY+1);
						repaint();
					}
					break;
				case KeyEvent.VK_LEFT:
					if(dialogSentence==null){
						face=Character.FACE_WEST;
						if(currentX!=0) moveCharacter(currentX-1,currentY);
						repaint();
					}
					break;
				case KeyEvent.VK_ENTER:
					if(dialogSentence!=null){
						for(int a=0;a<dialogOptionTextAreas.size();a++) dialogPanel.remove(dialogOptionTextAreas.get(a));
						dialogOptionTextAreas.clear();
						if(dialogSentence.isLeaf()){
							removeAll();
							dialogSentence=null;
						}else{
							dialogSentence=(Sentence)dialogSentence.getChildAt(sentenceSelected);
						}
						sentenceSelected=0;
						repaint();
					}else switch(face){
						case Character.FACE_NORTH:
							if(currentY!=0)check(currentX,currentY-1);
							break;
						case Character.FACE_EAST:
							if(currentX!=blockHorizontal-1)check(currentX+1,currentY);
							break;
						case Character.FACE_SOUTH:
							if(currentY!=blockVertical-1)check(currentX,currentY+1);
							break;
						case Character.FACE_WEST:
							if(currentY!=blockVertical-1)check(currentX-1,currentY);
							break;
					}
					break;
				case KeyEvent.VK_ESCAPE:
					if(game.getMenu()!=null){
						game.getMenu().removeAllCharacter();
						for(int a=0;a<characters.size();a++) game.getMenu().addCharacter(characters.get(a));
						game.switchToMenu();
					}
			}
		}
	};

	private ActionListener animate=new ActionListener(){
		public void actionPerformed(ActionEvent ae){
			if(aniPhase==1) aniPhase=2;
			else aniPhase=1;
			if(posX<toX)posX+=aniSpeed;
			else if(posX>toX)posX-=aniSpeed;
			if(posY<toY)posY+=aniSpeed;
			else if(posY>toY)posY-=aniSpeed;
			repaint();
			if(posX==toX&&posY==toY){
				aniTimer.stop();
				aniPhase=0;
				repaint();
				if(map[currentX][currentY]==TYPE_ENDPOINT&&mOnEndPoint!=null){
					mOnEndPoint.onEndPoint(RPGMap.this,currentX,currentY);
				}
			}
		}
	};

	Timer aniTimer=new Timer(aniInterval,animate);

	public RPGMap(RPGGame g){
		this(32,32,g,"m");
	}
    public RPGMap(int bwidth,int bheight,RPGGame g,String name){
        mapName=name;
        try{
            mapFile.load(new FileInputStream(mapName+".properties"));
        }catch(Exception ex){
            ex.printStackTrace();
            return;
        }
        int horizontal=Integer.parseInt(mapFile.getProperty("RowNum"));
        int vertical=Integer.parseInt(mapFile.getProperty("ColNum"));
        this(horizontal,vertical,bwidth,bheight,g);
        setupMap();
    }
	public RPGMap(int horizontal,int vertical,int bwidth,int bheight,RPGGame g){
        horizontal=Integer.parseInt(mapFile.getProperty("RowNum"));
        vertical=Integer.parseInt(mapFile.getProperty("ColNum"));
        game=g;
		map=new int[horizontal][vertical];
		mapLayer=new Image[horizontal][vertical];
		itemLayer=new Image[horizontal][vertical];
		wallLayer=new Image[horizontal][vertical];
		chests=new Chest[horizontal][vertical];
		bosses=new Boss[horizontal][vertical];
		npcs=new NPC[horizontal][vertical];
		npcLayer=new Image[horizontal][vertical];
		blockHorizontal=horizontal;
		blockVertical=vertical;
		blockWidth=bwidth;
		blockHeight=bheight;
		toY=posY=(-1)*blockHeight;
		dialogScrollPane.setOpaque(false);
		dialogScrollPane.setBorder(null);
		dialogScrollPane.getViewport().setOpaque(false);
		dialogScrollPane.getViewport().setLayout(new BoxLayout(dialogScrollPane.getViewport(),BoxLayout.X_AXIS));
		dialogPanel.setOpaque(false);
		dialogPanel.add(dialogMainTextArea);
		dialogPanel.setAlignmentX(Component.LEFT_ALIGNMENT);
		dialogPanel.setLayout(new BoxLayout(dialogPanel,BoxLayout.Y_AXIS));
		dialogMainTextArea.setOpaque(false);
		dialogMainTextArea.setForeground(Color.white);
		dialogMainTextArea.setEditable(false);
		dialogFont=dialogMainTextArea.getFont().deriveFont(18.0f);
		dialogMainTextArea.setFont(dialogFont);
		addKeyListener(keyAction);
		setFocusable(true);
		requestFocus();
        this.setupMap();
	}

	public void setBattleFeild(BattleFeild b){
		bf=b;
	}

	public void setCharacter(Character c){
		cha=c;
		if(characters.contains(cha)) Collections.swap(characters,characters.indexOf(cha),0);
		else characters.add(0,cha);
		for(int a=0;a<12;a++)characterImage[a]=c.getDirectedImage(a).getScaledInstance(blockWidth,blockHeight*2,Image.SCALE_FAST);
	}

	public void addCharacter(Character c){
		characters.add(c);
	}

	public void setDialogBackground(String path){
		dialogBackgroundPath=path;
	}

	public void setAnimationSpeed(int interval,int step){
		aniInterval=interval;
		aniSpeed=step;
		aniTimer=new Timer(interval,animate);
	}

	public void setTotalEncounterRate(int percent){
		encounterRate=percent;
	}

	public void addEnemy(Enemy a,int mul,int level){
	}

	public void addBoss(Boss b,int x,int y){
		itemLayer[x][y]=b.getMapImage().getScaledInstance(blockWidth,blockHeight,Image.SCALE_FAST);
		bosses[x][y]=b;
	}

	public void addNPC(NPC n,int x,int y){
		npcLayer[x][y]=n.getImage().getScaledInstance(blockWidth,blockHeight*2,Image.SCALE_FAST);
		setBlockType(x,y,TYPE_BLOCK);
		npcs[x][y]=n;
	}

	public void addChest(Chest c,int x,int y){
		chests[x][y]=c;
		itemLayer[x][y]=c.getImage().getScaledInstance(blockWidth,blockHeight,Image.SCALE_FAST);
		setBlockType(x,y,TYPE_BLOCK);
	}

	public void addDialog(Sentence s){
		if(dialogSentence==null){
			dialogSentence=s;
		}
	}

	public void setOnEndPointListener(OnEndPointListener a){
		mOnEndPoint=a;
	}

	public void setOnMoveListener(OnMoveListener a){
		mOnMove=a;
	}

	public void setOnCheckListener(OnCheckListener a){
		mOnCheck=a;
	}

	private void moveCharacter(int x,int y){
		if(posX!=toX||posY!=toY||dialogSentence!=null) return;
		// FIXME : make this better
		if(map[x][y]==TYPE_ENDPOINT||map[x][y]==TYPE_WALKABLE||(map[x][y]==TYPE_HORIZONTAL_WALKABLE&&(face==Character.FACE_WEST||face==Character.FACE_EAST))
			||(map[x][y]==TYPE_VERTICAL_WALKABLE&&(face==Character.FACE_NORTH||face==Character.FACE_SOUTH))){
			toX=x*blockWidth;
			toY=(y-1)*blockHeight;
			currentX=x;
			currentY=y;
			aniTimer.start();
		}
		repaint();
		if(mOnMove!=null) mOnMove.onMove(this,x,y);
	}

	private void check(int x,int y){
		if (chests[x][y]!=null&&chests[x][y].isUsed()==false){
			chests[x][y].open(this,game);
			itemLayer[x][y]=chests[x][y].getUsedImage().getScaledInstance(blockWidth,blockHeight,Image.SCALE_FAST);
		}
		else if(npcs[x][y]!=null){
			int dir=0;
			switch (face){
				case Character.FACE_NORTH:
					dir=NPC.FACE_SOUTH;
					break;
                                case Character.FACE_SOUTH:
                                        dir=NPC.FACE_NORTH;
                                        break;
                                case Character.FACE_EAST:
                                        dir=NPC.FACE_WEST;
                                        break;
                                case Character.FACE_WEST:
                                        dir=NPC.FACE_EAST;
                                        break;
			}
			npcLayer[x][y]=npcs[x][y].getDirectedImage(dir).getScaledInstance(blockWidth,blockHeight*2,Image.SCALE_FAST);
			if(npcs[x][y].getDialog()!=null){
				addDialog(npcs[x][y].getDialog());
			}
			repaint();
		}
		else if(bosses[x][y]!=null){
			//battle
		}
		if(mOnCheck!=null) mOnCheck.onCheck(this,x,y);
	}

	public void setLocation(int x,int y){
		currentX=x;
		currentY=y;
		toX=posX=currentX*blockWidth;
		toY=posY=(currentY-1)*blockHeight;
		aniPhase=0;
	}

	public void setBlockType(int x,int y,int type){
		map[x][y]=type;
	}

	public void setAllBlockType(int type){
		for(int a=0;a<blockHorizontal;a++)
			for(int b=0;b<blockVertical;b++)
				map[a][b]=type;
	}

	public void setBlockImage(String path,int type){
		blockImages[type]=Utils.getScaledImage(path,blockWidth,blockHeight);
	}

	public void setMapLayerOverlap(String path,int x,int y){
		mapLayer[x][y]=Utils.getScaledImage(path,blockWidth,blockHeight);
	}

	public void setItemLayerOverlap(String path,int x,int y){
		itemLayer[x][y]=Utils.getScaledImage(path,blockWidth,blockHeight);
	}

	public void setWallLayerOverlap(String path,int x,int y){
		wallLayer[x][y]=Utils.getScaledImage(path,blockWidth,blockHeight);
	}

	public void setNPCLayerOverlap(String path,int x,int y){
		npcLayer[x][y]=Utils.getScaledImage(path,blockWidth,blockHeight*2);
	}

	@Override
	public void paintComponent(Graphics g){
		super.paintComponent(g);
		g.setColor(Color.black);
		g.fillRect(0,0,getSize().width,getSize().height);
		int windowWidth=getSize().width;
		int windowHeight=getSize().height;
		int windowCenterW=windowWidth/2-blockWidth/2;
		int windowCenterH=windowHeight/2-blockHeight;
		/*
		 * FIXME: there is still chance that scaling is not done while drawing
		 *  go for a further test on low-end device and call dialog on first draw
		 *  or find another way to do this.
		 */
		if(dialogBackgroundPath!=null&&dialogBackground==null) dialogBackground=Utils.getScaledImage(dialogBackgroundPath,windowWidth,windowHeight/3);
		for(int a=0;a<blockVertical;a++){
			for(int b=0;b<blockHorizontal;b++){
				int locX=b*blockWidth-posX+windowCenterW;
				int locY=a*blockHeight-posY+windowCenterH;
				if(locX>=(-blockWidth)&&locX<=windowWidth&&locY>=(-blockHeight)&&locY<=windowHeight){
					if (mapLayer[b][a]!=null) g.drawImage(mapLayer[b][a],locX,locY,this);
					else if(blockImages[map[b][a]]!=null) g.drawImage(blockImages[map[b][a]],locX,locY,this);
					if (itemLayer[b][a]!=null) g.drawImage(itemLayer[b][a],locX,locY,this);
					if (npcLayer[b][a]!=null) g.drawImage(npcLayer[b][a],locX,locY-blockHeight,this);
                        		if ((toX/blockHeight+1==b)&&((toY/blockHeight+1==a)||toY<posY)) g.drawImage(characterImage[face+aniPhase*4],windowCenterW,windowCenterH,this);
					if (wallLayer[b][a]!=null) g.drawImage(wallLayer[b][a],locX,locY,this);
				}
			}
		}
		if(dialogSentence!=null){
			add(dialogScrollPane);
                        g.drawImage(dialogBackground,0,windowHeight/3*2,this);
			Image protrait=dialogSentence.getProtrait();
			dialogMainTextArea.setText(dialogSentence.getContent());
			if(dialogProtraitWidth==0) dialogProtraitWidth=windowHeight/3/4*3;
			if(dialogMinSize==null){
				dialogMinSize=new Dimension(windowWidth-20,1);
				dialogMaxSize=new Dimension(windowWidth-20,Integer.MAX_VALUE);
				dialogWithProtraitMinSize=new Dimension(windowWidth-dialogProtraitWidth,1);
				dialogWithProtraitMaxSize=new Dimension(windowWidth-10-dialogProtraitWidth,Integer.MAX_VALUE);
			}
			if(protrait==null){
				dialogScrollPane.setBounds(0,windowHeight/3*2,windowWidth,windowHeight/3);
				dialogPanel.setMinimumSize(dialogMinSize);
				dialogPanel.setMaximumSize(dialogMaxSize);
                                dialogMainTextArea.setColumns(windowWidth/dialogMainTextArea.getFontMetrics(dialogMainTextArea.getFont()).charWidth('一')-3);

			}
			else{
				//protrait=protrait.getScaledInstance(windowHeight/3/4*3,windowHeight/3,Image.SCALE_FAST);
				//FIXME: fallback to below to prevent incomplete scaling, scaled should be cached
				g.drawImage(protrait,0,windowHeight/3*2,windowHeight/3/4*3,windowHeight/3,this);
				dialogScrollPane.setBounds(windowHeight/3/4*3,windowHeight/3*2,windowWidth-windowHeight/3/4*3,windowHeight/3);
                                dialogPanel.setMinimumSize(dialogWithProtraitMinSize);
                                dialogPanel.setMaximumSize(dialogWithProtraitMaxSize);
                                dialogMainTextArea.setColumns((windowWidth-dialogProtraitWidth)/dialogMainTextArea.getFontMetrics(dialogMainTextArea.getFont()).charWidth('一')-3);

			}
			if(dialogSentence.getChildCount()>1){
				if(dialogOptionTextAreas.isEmpty()){
					for(int a=0;a<dialogSentence.getChildCount();a++){
						JTextArea tmp=new JTextArea();
						dialogOptionTextAreas.add(tmp);
						tmp.setBackground(Utils.TRANSPARENT);
						tmp.setEditable(false);
						tmp.setForeground(Color.white);
                                		tmp.setColumns(((protrait==null)?windowWidth:windowWidth-dialogProtraitWidth)/tmp.getFontMetrics(tmp.getFont()).charWidth('一')-3);
						tmp.setText(((Sentence) dialogSentence.getChildAt(a)).getSelectionText());
						tmp.setFont(dialogFont);
						dialogPanel.add(tmp);
					}
				}
				dialogOptionTextAreas.get(sentenceSelected).setBackground(Utils.HILIGHT);
			}
			dialogMainTextArea.setLocation(0,0);
		}
	}
	private void setupMap(){
        String[] blockTypeC=mapFile.getProperty("BlockType").split(";");
        String[] blockList=mapFile.getProperty("BlockList").split(",");
        String[] blockTableC=mapFile.getProperty("BlockTable").split(";");
        for(int  i=0;i<blockVertical;i++){
            String[] blockTable=blockTableC[i].split(",");
            String[] blockType=blockTypeC[i].split(",");
            for (int j=0;j<blockHorizontal;j++){
                this.setBlockType(i,j,Integer.parseInt(blockType[j]));
                this.setMapLayerOverlap(blockList[Byte.parseByte(blockTable[j])],i,j);
            }
        }
	}
}
