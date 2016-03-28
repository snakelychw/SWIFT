//
//  ViewController.swift
//  Calculator
//
//  Created by Henry on 12/2/15.
//  Copyright © 2015 Henry. All rights reserved.
//

import UIKit

class ViewController: UIViewController
{

    @IBOutlet weak var display: UILabel!
    
    var userTyping: Bool = false
    
    @IBAction func appdendDigit(sender: UIButton) {
        let digit = sender.currentTitle! //swift is strongly typed. but digit auto match type of sender.currentTitle
        if userTyping {
            display.text = display.text! + digit} else {
            display.text=digit
            userTyping=true
        }
        print("digit= \(digit)")
    }
    
    var operandStack = Array<Double>()
  //var operandStack: Array<Double> = Array<Double>()
    @IBAction func enter() {
        userTyping = false
        operandStack.append(displayValue)
        print(operandStack)
    }
    
    @IBAction func operate(sender: UIButton) {
        let operation = sender.currentTitle!
        if userTyping{
            enter()
        }
        switch operation{
            case "✕":
                performOperarion({ $0 * $1 })
            case "÷":
                performOperarion({ $1 / $0 })
            case "+":
                performOperarion({ $0 + $1 })
            case "-":
            performOperarion({ $1 - $0 })
            default: break
        }
        
    }
    
    func performOperarion(operation: (Double, Double)->Double) {
        if operandStack.count >= 2 {
            displayValue = operation(operandStack.removeLast(), operandStack.removeLast())
            enter()
        }
    }
    
    
    
    var displayValue: Double {
        get {
            return NSNumberFormatter().numberFromString(display.text!)!.doubleValue
        }
        set{
            display.text = "\(newValue)" //newValue of displayBValue
            userTyping = false
        }
        
    }
}

