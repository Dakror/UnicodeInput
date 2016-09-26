# UnicodeInput
A Simple Windows background program to write unicode characters like emojis. 
Usable as macro system for programmable keyboards without a paste functionality (like my Corsair K95 😅)
## Why?
On windows, you can't really type Unicode characters that aren't directly linked to keys on your keyboard. With Alt + Numpad you get some symbols, but not a whole lot, and even with the Registry Modification to enable the Hex NumPad, you're still limited to 4 hex digits, so everything past U+FFFF is off limits. But if I want to macro emojis for usage in Whatsapp Web or the standalone version, I'm screwed. So that's why I wrote this little tool.

## Usage
`ctrl + alt + NumPad: < Unicode Codepoint in HEX > `
On key release, the unicode symbol will be placed where your current input focus lies.

### Examples

`ctrl + alt + (1) + (F) + (6) + (0) + (2)` => 😂 (U+1F602)

`ctrl + alt + (2) + (7) + (6) + (4)`=> ❤  (U+2764)

## Download
Get the binary: [http://dakror.de/dl/UnicodeInput.exe](http://dakror.de/dl/UnicodeInput.exe)

## Contribution
Please report any bugs and share your ideas to improve this tiny program further 😊

PRs are welcome.

## Licence
 Copyright 2016 Maximilian Stark | Dakror <mail@dakror.de>
  
  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at
  
    http://www.apache.org/licenses/LICENSE-2.0
  
  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
