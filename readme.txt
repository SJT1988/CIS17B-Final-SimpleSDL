This is the README for our CIS-17B project. It was offered solely by Spencer Trumbore and is only my perspective. This game is the result of a month of hard work by a team of very talented new developers.

CAUTION: In order to run the project in Visual Studio, you COULD need to manually set the compiler mode back to x86, because I deleted the .vs folder to make the zip file smaller.

//+--------------+
//|   GAMEPLAY   |
//+--------------+

The player controlls Rick Tangle, a private-eye who is breaking into a sequence of basements filled with traps and giant spiders. You can move Rick with the WASD keys and shoot with the spacebar. Rick can move and shoot in each octogonal direction.

* Hazzards:
    * Web: If Rick gets stuck in a web, he can't move for 1 second.
    * Spikes: If Rick touches a spike trap, he will die instantly.
    * Monsters: If a spider touches rick, he will die instantly.

A death means restarting the entire game (The game is neat, I didn't say we made it perfect or exactly how we would like by the tme we submitted it).

//+-------------------+
//|   WE GOT ISSUES   |
//+-------------------+

Two outstanding issues: first, the spiders are arguably too fast and too many in the latter half of the game. Second, the High Score counter doesn't work reliably and cannot carry over to the start screen because I decided to set it for destruction whenever scenes are switched. This was a "lazy" way to sweep a bug under the rug where I couldn't figure out how to reset animations for SDL 2.0's color modulation.

I will get these fixed when I have more time.

//+----------------+
//|   DEVELOPERS   |
//+----------------+

Spencer Trumbore
Kristian Dompor
Shuai "William" Xiong

//+-------------+
//|   DEV LOG   |
//+-------------+

Our duties for this project often overlapped, particularly when it came to resolving bugs and errors. Kristian was especially helpful in showing me when I forgot to use a comparison operator `==` instead of the assignment operator `=` for an IF statement. William taught me how to use the Visual Studio debugger, which I had been neglecting for a year.

We started this project in earnest at least 2 weeks after it was first assigned. I think it is fair to say that all of us (and there were four of us when we started) felt overwhelmed by the task in front of us. We did not know anything about SDL 2.0 and had no idea where to start or how deep we would need to dive to have anything to show for our progress. Kristian had created a Discord account for us the day the project was assigned, and I started making a log of my progress following an SDL 2.0 RPG tutorial by Carl Birch on Youtube. This started in earnest on 11/06/19.

By 11/12/19 (less than a week) I had created a prototype room with a fully animated character, using a text file tile-mapping method commonly used to make 2d games without an engine.

We had our first meeting between then and 11/16/19. William helped me resolve some bugs I was experiencing. We created the monster and its animations together.

On 11/16/19, I resolved the last bugs that were preventing bullets from firing and posted an animated gif on discord. There were still lots of bugs, however.

We had another meeting on 11/22/19 where some more issues were resolved. Kristian gave the monster some neat properties, including random sizing, random speeds and AI.

Our project deviated significantly from Carl Birch's Youtube tutorial by this point and we had finished all of his videos without instructions on how to swtich scenes or a hint at a design pattern that would facilitate this; later videos always refactored work in previous videos, which made even what we already had feel flimsy to me, at best. I looked for another tutorial that would explain how to do switch scenes. I found that in Ather Omar's SDL 2.0 "Galaga" tutorial.

By 11/30/19 I built the `StartScreen` and began the `PlayScreen`. I swiped a music track from Super Mario RPG and editted it until it looped seemlessly, then put it in the game.

By 12/04/19 I got the level prototype back into the game along with the character and all his animations. Bullets were not back yet. I successfully designed and implemented a level switcher that would load new maps (levels) into the PlayScreen.

On 12/06/19 I realized that older levels were not being deleted like I thought they were and plugged that leak.

From 12/06/19 to the moment we presented (12/09/19), a lot happened quickly. We had 4 meetings in a row: Friday, Saturday, Sunday and Monday. William created a program that generates random mazes using our tileset image (which he procured some reference images for, by the way). These became our final levels. Kristian worked diligently on fixing the mess I made of the bullet-firing mechanism in the new framework. Over the course of the entire project, I made the collision class 3 times. My second attempt followed the Galaga tutorial closely and involved a heirarchy of 3 new classes. It was a mess and bugs in placement and scale confounded me. On Sunday, 12/08/19, I built it for the third time according to my own intuitive sense of what the class should do, and it worked exactly how I intended it to. Each `Collider` has an enum ("tag") property that tells the program what to do when the player or an enemy's collider comes in contact with it. Different tags include `player`, `monster`, `wall`, `bullet`, `web`, and `spikes`. On the day of presentation, I finished the collision resolution for bullets, spikes, webs and monsters.

During the evening after presentation, I resolved some bugs with the monsters where they were not getting destroyed properly, and added a Credits scene to the main menu, plus another sound effect.