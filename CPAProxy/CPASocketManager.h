//  CPASocketManager.h
//
//  Copyright (c) 2013 Claudiu-Vlad Ursache.
//  See LICENCE for licensing information
//

#import <Foundation/Foundation.h>

@protocol CPASocketManagerDelegate;

/**
 A `CPASocketManager` is responsible for reading and writing data to a socket that is usually connected to a Tor client's control port.
 */
@interface CPASocketManager : NSObject

/**
 Returns YES if the socket manager has a connected socket, NO otherwise.
 */
@property (nonatomic, readonly) BOOL isConnected;

/**
 Returns the socket manager's delegate.
 */
@property (nonatomic, readonly, weak) id<CPASocketManagerDelegate> delegate;

/**
 Initializes a `CPASocketManager` with the specified delegate.
 
 @param delegate The delegate responsing to socket events.
 @return A newly initialized `CPASocketManager` 
 */
- (instancetype)initWithDelegate:(id<CPASocketManagerDelegate>)delegate;

/**
 Attempts to create and connect a socket to the specified host and port and calls the delegate method `socketManagerDidOpenSocket:` or `socketManagerDidFailToOpenSocket:` depending on the result.
 
 @param host The hostname to connect to.
 @param port The port to connect to.
 */
- (void)connectToHost:(NSString *)host port:(NSUInteger)port;

/**
 Writes a string to the already connected socket. If the socket hasn't been created and connected by calling `connectToHost:port:`, the method returns without doing anything.
 
 @param string The string to be written to the socket.
 @param encoding The encoding of the string.
 */
- (void)writeString:(NSString *)string encoding:(NSStringEncoding)encoding;

@end

/**
 Socket timeout delay for a call to -connectToHost:port:
 */
extern const NSTimeInterval CPASocketTimeoutDelay;

/**
 The CPASocketManagerDelegate defines methods used to respond to events related to the manager's socket.
 */
@protocol CPASocketManagerDelegate <NSObject>

/**
 This method is called when a `CASocketManager` has successfully created and connected a socket to the host and port specified by `-connectToHost:port:`.
 
 @see -connectToHost:port:
 */
- (void)socketManagerDidOpenSocket:(CPASocketManager *)manager;

/**
 This method is called when a `CASocketManager` has failed to connect to a socket after calling `-connectToHost:port:`.
 
  @see -connectToHost:port:
 */
- (void)socketManagerDidFailToOpenSocket:(CPASocketManager *)manager;

/**
 This method is called when data has been read from the socket as a response to -writeString:encoding:
 
  @see -writeString:encoding:
 */
- (void)socketManager:(CPASocketManager *)manager didReceiveResponse:(NSString *)response;
@end